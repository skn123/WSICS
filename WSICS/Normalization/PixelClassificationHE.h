#ifndef __WSICS_NORMALIZATION_PIXELCLASSIFICATIONHE__
#define __WSICS_NORMALIZATION_PIXELCLASSIFICATIONHE__

#include <multiresolutionimageinterface/MultiResolutionImage.h>
#include <opencv2/core/core.hpp>

#include "../HE_Staining/HE_Classifier.h"
#include "../HE_Staining/MaskGeneration.h"
#include "../HSD/HSD_Model.h"

#include "WSICS_Parameters.h"

namespace WSICS::Normalization
{
	typedef HE_Staining::ClassificationResults ClassificationResults;
	typedef HE_Staining::EosinMaskInformation EosinMaskInformation;
	typedef HE_Staining::HematoxylinMaskInformation HematoxylinMaskInformation;

	struct TrainingSampleInformation
	{
		cv::Mat training_data_cx_cy;
		cv::Mat training_data_density;
		cv::Mat class_data;
	};

	class PixelClassificationHE
	{
		public:
			PixelClassificationHE(bool consider_ink, size_t log_file_id, std::string debug_dir);

			TrainingSampleInformation GenerateCxCyDSamples(
				MultiResolutionImage& tiled_image,
				const cv::Mat& static_image,
				const WSICS_Parameters& parameters,
				const std::vector<cv::Point>& tile_coordinates,
				const std::vector<double>& spacing,
				const uint32_t tile_size,
				const uint32_t min_level,
				const bool is_multiresolution_image);

		private:
			bool		m_consider_ink_;
			size_t		m_log_file_id_;
			std::string m_debug_dir_;

			std::pair<HematoxylinMaskInformation, EosinMaskInformation> Create_HE_Masks_(
				const HSD::HSD_Model& hsd_image,
				const cv::Mat& background_mask,
				const uint32_t tile_id,
				const uint32_t max_training_size,
				const int32_t min_ellipses,
				const float hema_percentile,
				const float eosin_percentile,
				const std::vector<double>& spacing,
				const bool is_multiresolution);


			/// <param name="total_hema_count">The current total count of the Hematoxylin pixels. Warning: This methods updates the value with newly discovered pixels.</param>
			/// <param name="total_eosin_count">The current total count of the Eosin pixels. Warning: This methods updates the value with newly discovered pixels.</param>
			/// <param name="total_background_count">The current total count of the background pixels. Warning: This methods updates the value with newly discovered pixels.</param>
			TrainingSampleInformation InsertTrainingData_(
				const HSD::HSD_Model& hsd_image,
				const ClassificationResults& classification_results,
				TrainingSampleInformation& sample_information,
				size_t& total_hema_count,
				size_t& total_eosin_count,
				size_t& total_background_count,
				const uint32_t max_training_size);

			TrainingSampleInformation PatchTestData_(const size_t non_zero_count, const TrainingSampleInformation& current_sample_information);
	};
}
#endif // __WSICS_NORMALIZATION_PIXELCLASSIFICATIONHE__