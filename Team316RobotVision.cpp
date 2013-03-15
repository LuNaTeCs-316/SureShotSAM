//
// Team316RobotVision.cpp
//

#include <cmath>
#include "Team316Robot.h"
#include "Vision/RGBImage.h"

struct Scores
{
	double rectangularity;
	double aspectRatioInner;
	double aspectRatioOuter;
	double xEdge;
	double yEdge;
};

double ScoreRectangularity(ParticleAnalysisReport* report);
double ScoreAspectRatio(BinaryImage* image, ParticleAnalysisReport* report, bool outer);
double ScoreXEdge(BinaryImage* image, ParticleAnalysisReport* report);
double ScoreYEdge(BinaryImage* image, ParticleAnalysisReport* report);
bool ScoreCompare(Scores scores, bool outer);
double ComputeDistance (BinaryImage *image, ParticleAnalysisReport *report, bool outer);

//Edge profile constants used for hollowness score calculation
#define XMAXSIZE 24
#define XMINSIZE 24
#define YMAXSIZE 24
#define YMINSIZE 48
const double xMax[XMAXSIZE] = {1, 1, 1, 1, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, 1, 1, 1, 1};
const double xMin[XMINSIZE] = {.4, .6, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, 0.6, 0};
const double yMax[YMAXSIZE] = {1, 1, 1, 1, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, 1, 1, 1, 1};
const double yMin[YMINSIZE] = {.4, .6, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05,
								.05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05,
								.05, .05, .6, 0};

//Score limits used for target identification
#define RECTANGULARITY_LIMIT 60
#define ASPECT_RATIO_LIMIT 75
#define X_EDGE_LIMIT 40
#define Y_EDGE_LIMIT 60

//Camera constants used for distance calculation
#define X_IMAGE_RES 320		//X Image resolution in pixels, should be 160, 320 or 640
#define VIEW_ANGLE 48		//Axis 206 camera
//#define VIEW_ANGLE 43.5  //Axis M1011 camera
#define PI 3.141592653

void Team316Robot::ProcessCameraImage()
{
	// Get the camera object
	AxisCamera& camera = AxisCamera::GetInstance();
	Threshold threshold(0, 100, 60, 255, 0, 170);
	ParticleFilterCriteria2 criteria[] = {
			{IMAQ_MT_AREA, 500, 65535, false, false}
	};
	
	if (&camera)	// check to make sure camera exists
	{
		static bool cameraSetupDone = false;
		if (!cameraSetupDone)
		{
			// Perform one time setup
			camera.WriteCompression(30);
			camera.WriteResolution(AxisCameraParams::kResolution_160x120);
			camera.WriteWhiteBalance(AxisCameraParams::kWhiteBalance_Hold);
			camera.WriteExposureControl(AxisCameraParams::kExposure_Hold);
			cameraSetupDone = true;
		}
		
		// Grab an image from the camera
		if (camera.IsFreshImage())
		{
			ColorImage* image = camera.GetImage();
			
			// Check to make sure image exists
			if (image)
			{
				// Apply RGB Threshold to mask green
				BinaryImage* thresholdImage = image->ThresholdRGB(threshold);
				thresholdImage->Write("thresholdImage.jpg");
				// Apply convex hull to fill in rectangle
				BinaryImage* convexHullImage = thresholdImage->ConvexHull(false);
				convexHullImage->Write("convexHullImage.jpg");
				// Apply particle filter to remove small blobs
				BinaryImage* filteredImage = convexHullImage->ParticleFilter(criteria, 1);
				filteredImage->Write("filteredImage.jpg");
				// Get particle analysis reports
				vector<ParticleAnalysisReport>* reports = filteredImage->GetOrderedParticleAnalysisReports();
				
				Scores* scores = new Scores [reports->size()];
				
				for (size_t i = 0; i < reports->size(); i++)
				{
					ParticleAnalysisReport* report = &(reports->at(i));
					
					scores[i].rectangularity = ScoreRectangularity(report);
					scores[i].aspectRatioInner = ScoreAspectRatio(filteredImage, report, false);
					scores[i].aspectRatioOuter = ScoreAspectRatio(filteredImage, report, true);
					scores[i].xEdge = ScoreXEdge(thresholdImage, report);
					scores[i].yEdge = ScoreYEdge(thresholdImage, report);
					
					if (ScoreCompare(scores[i], false))
					{
						printf("particle: %d  is a High Goal  centerX: %f  centerY: %f \n", i, report->center_mass_x_normalized, report->center_mass_y_normalized);
						printf("Distance: %f \n", ComputeDistance(thresholdImage, report, false));
					}
					else if (ScoreCompare(scores[i], true))
					{
						printf("particle: %d  is a Middle Goal  centerX: %f  centerY: %f \n", i, report->center_mass_x_normalized, report->center_mass_y_normalized);
						printf("Distance: %f \n", ComputeDistance(thresholdImage, report, true));
					}
					else
					{
						printf("particle: %d  is not a goal  centerX: %f  centerY: %f \n", i, report->center_mass_x_normalized, report->center_mass_y_normalized);
					}
					printf("rect: %f  ARinner: %f \n", scores[i].rectangularity, scores[i].aspectRatioInner);
					printf("ARouter: %f  xEdge: %f  yEdge: %f  \n", scores[i].aspectRatioOuter, scores[i].xEdge, scores[i].yEdge);
				}
				printf("\n");
				
				delete filteredImage;
				delete convexHullImage;
				delete thresholdImage;
			}
			else
			{
				std::cout << "Error: image could not be obtained" << std::endl;
			}
			delete image;
		}
	}
	else
		std::cout << "Error: failed to get camera" << std::endl;
}

//
// ScoreRectangularity(report)
//
// Evaluates rectangularity of particle, scoring from 0-100
//
double ScoreRectangularity(ParticleAnalysisReport* report)
{
	if (report->boundingRect.width * report->boundingRect.height != 0)
		return (100 * ((report->particleArea) / 
				(report->boundingRect.width*report->boundingRect.height)));
	else
		return 0;
}

//
// ScoreAspectRatio
//
// Measures aspect ratio and compares to the ideal aspect ratio for the target
//
double ScoreAspectRatio(BinaryImage* image, ParticleAnalysisReport* report, bool outer)
{
	double rectLong, rectShort, idealAspectRatio, aspectRatio;
	idealAspectRatio = outer ? (62/29) : (62/20);
	
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
	
	if (report->boundingRect.width > report->boundingRect.height)
		aspectRatio = 100*(1-fabs((1-((rectLong/rectShort)/idealAspectRatio))));
	else
		aspectRatio = 100*(1-fabs((1-((rectShort/rectLong)/idealAspectRatio))));
	return (max(0, min(aspectRatio, 100)));
}

/**
 * Computes a score based on the match between a template profile and the particle profile in the X direction. This method uses the
 * the column averages and the profile defined at the top of the sample to look for the solid vertical edges with
 * a hollow center.
 * 
 * @param image The image to use, should be the image before the convex hull is performed
 * @param report The Particle Analysis Report for the particle
 * 
 * @return The X Edge Score (0-100)
 */
double ScoreXEdge(BinaryImage* image, ParticleAnalysisReport* report)
{
	double total = 0;
	LinearAverages *averages = imaqLinearAverages2(image->GetImaqImage(), IMAQ_COLUMN_AVERAGES, report->boundingRect);
	for(int i=0; i < (averages->columnCount); i++){
		if(xMin[i*(XMINSIZE-1)/averages->columnCount] < averages->columnAverages[i] 
		   && averages->columnAverages[i] < xMax[i*(XMAXSIZE-1)/averages->columnCount]){
			total++;
		}
	}
	total = 100*total/(averages->columnCount);		//convert to score 0-100
	imaqDispose(averages);							//let IMAQ dispose of the averages struct
	return total;
}

/**
 * Computes a score based on the match between a template profile and the particle profile in the Y direction. This method uses the
 * the column averages and the profile defined at the top of the sample to look for the solid vertical edges with
 * a hollow center.
 * 
 * @param image The image to use, should be the image before the convex hull is performed
 * @param report The Particle Analysis Report for the particle
 * 
 * @return The Y Edge Score (0-100)
 */
double ScoreYEdge(BinaryImage* image, ParticleAnalysisReport* report)
{
	double total = 0;
	LinearAverages *averages = imaqLinearAverages2(image->GetImaqImage(), IMAQ_ROW_AVERAGES, report->boundingRect);
	for(int i=0; i < (averages->rowCount); i++){
		if(yMin[i*(YMINSIZE-1)/averages->rowCount] < averages->rowAverages[i] 
		   && averages->rowAverages[i] < yMax[i*(YMAXSIZE-1)/averages->rowCount]){
			total++;
		}
	}
	total = 100*total/(averages->rowCount);		//convert to score 0-100
	imaqDispose(averages);						//let IMAQ dispose of the averages struct
	return total;
}

/**
 * Compares scores to defined limits and returns true if the particle appears to be a target
 * 
 * @param scores The structure containing the scores to compare
 * @param outer True if the particle should be treated as an outer target, false to treat it as a center target
 * 
 * @return True if the particle meets all limits, false otherwise
 */
bool ScoreCompare(Scores scores, bool outer)
{
	bool isTarget = true;

	isTarget &= scores.rectangularity > RECTANGULARITY_LIMIT;
	if(outer){
		isTarget &= scores.aspectRatioOuter > ASPECT_RATIO_LIMIT;
	} else {
		isTarget &= scores.aspectRatioInner > ASPECT_RATIO_LIMIT;
	}
	isTarget &= scores.xEdge > X_EDGE_LIMIT;
	isTarget &= scores.yEdge > Y_EDGE_LIMIT;

	return isTarget;
}

/**
 * Computes the estimated distance to a target using the height of the particle in the image. For more information and graphics
 * showing the math behind this approach see the Vision Processing section of the ScreenStepsLive documentation.
 * 
 * @param image The image to use for measuring the particle estimated rectangle
 * @param report The Particle Analysis Report for the particle
 * @param outer True if the particle should be treated as an outer target, false to treat it as a center target
 * @return The estimated distance to the target in Inches.
 */
double ComputeDistance (BinaryImage *image, ParticleAnalysisReport *report, bool outer)
{
	double rectShort, height;
	int targetHeight;
	
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
	//using the smaller of the estimated rectangle short side and the bounding rectangle height results in better performance
	//on skewed rectangles
	height = min(report->boundingRect.height, rectShort);
	targetHeight = outer ? 29 : 21;
	
	return X_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(VIEW_ANGLE*PI/(180*2)));
}
