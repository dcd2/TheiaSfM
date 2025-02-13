// Copyright (C) 2013 The Regents of the University of California (Regents).
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//
//     * Neither the name of The Regents or University of California nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Please contact the author of this library if you have any questions.
// Author: Chris Sweeney (cmsweeney@cs.ucsb.edu)

#ifndef THEIA_THEIA_H_
#define THEIA_THEIA_H_

#include "theia/alignment/alignment.h"
#include "theia/image/descriptor/create_descriptor_extractor.h"
#include "theia/image/descriptor/descriptor_extractor.h"
#include "theia/image/descriptor/sift_descriptor.h"
#include "theia/image/image.h"
#include "theia/image/image_canvas.h"
#include "theia/image/keypoint_detector/keypoint.h"
#include "theia/image/keypoint_detector/keypoint_detector.h"
#include "theia/image/keypoint_detector/sift_detector.h"
#include "theia/image/keypoint_detector/sift_parameters.h"
#include "theia/io/read_1dsfm.h"
#include "theia/io/read_bundler_files.h"
#include "theia/io/read_calibration.h"
#include "theia/io/read_matches.h"
#include "theia/io/reconstruction_reader.h"
#include "theia/io/reconstruction_writer.h"
#include "theia/io/sift_binary_file.h"
#include "theia/io/sift_text_file.h"
#include "theia/io/write_bundler_files.h"
#include "theia/io/write_matches.h"
#include "theia/io/write_ply_file.h"
#include "theia/matching/brute_force_feature_matcher.h"
#include "theia/matching/cascade_hasher.h"
#include "theia/matching/cascade_hashing_feature_matcher.h"
#include "theia/matching/create_feature_matcher.h"
#include "theia/matching/distance.h"
#include "theia/matching/feature_correspondence.h"
#include "theia/matching/feature_matcher.h"
#include "theia/matching/feature_matcher_options.h"
#include "theia/matching/feature_matcher_utils.h"
#include "theia/matching/image_pair_match.h"
#include "theia/matching/indexed_feature_match.h"
#include "theia/math/closed_form_polynomial_solver.h"
#include "theia/math/distribution.h"
#include "theia/math/find_polynomial_roots_companion_matrix.h"
#include "theia/math/find_polynomial_roots_jenkins_traub.h"
#include "theia/math/graph/connected_components.h"
#include "theia/math/histogram.h"
#include "theia/math/l1_solver.h"
#include "theia/math/matrix/dominant_eigensolver.h"
#include "theia/math/matrix/gauss_jordan.h"
#include "theia/math/matrix/linear_operator.h"
#include "theia/math/matrix/rq_decomposition.h"
#include "theia/math/polynomial.h"
#include "theia/math/probability/sequential_probability_ratio.h"
#include "theia/math/util.h"
#include "theia/sfm/bundle_adjustment/angular_epipolar_error.h"
#include "theia/sfm/bundle_adjustment/bundle_adjust_track.h"
#include "theia/sfm/bundle_adjustment/bundle_adjust_two_views.h"
#include "theia/sfm/bundle_adjustment/bundle_adjust_view.h"
#include "theia/sfm/bundle_adjustment/bundle_adjustment.h"
#include "theia/sfm/bundle_adjustment/optimize_relative_position_with_known_rotation.h"
#include "theia/sfm/bundle_adjustment/orthogonal_vector_error.h"
#include "theia/sfm/bundle_adjustment/unit_norm_three_vector_parameterization.h"
#include "theia/sfm/camera/camera.h"
#include "theia/sfm/camera/project_point_to_image.h"
#include "theia/sfm/camera/projection_matrix_utils.h"
#include "theia/sfm/camera/radial_distortion.h"
#include "theia/sfm/camera/reprojection_error.h"
#include "theia/sfm/camera_intrinsics_prior.h"
#include "theia/sfm/estimate_track.h"
#include "theia/sfm/estimate_twoview_info.h"
#include "theia/sfm/estimators/estimate_calibrated_absolute_pose.h"
#include "theia/sfm/estimators/estimate_essential_matrix.h"
#include "theia/sfm/estimators/estimate_fundamental_matrix.h"
#include "theia/sfm/estimators/estimate_homography.h"
#include "theia/sfm/estimators/estimate_relative_pose.h"
#include "theia/sfm/estimators/estimate_triangulation.h"
#include "theia/sfm/estimators/estimate_uncalibrated_absolute_pose.h"
#include "theia/sfm/estimators/estimate_uncalibrated_relative_pose.h"
#include "theia/sfm/exif_reader.h"
#include "theia/sfm/feature.h"
#include "theia/sfm/feature_extractor.h"
#include "theia/sfm/feature_extractor_and_matcher.h"
#include "theia/sfm/filter_view_graph_cycles_by_rotation.h"
#include "theia/sfm/filter_view_pairs_from_orientation.h"
#include "theia/sfm/filter_view_pairs_from_relative_translation.h"
#include "theia/sfm/find_common_tracks_in_views.h"
#include "theia/sfm/find_common_views_by_name.h"
#include "theia/sfm/incremental_reconstruction_estimator.h"
#include "theia/sfm/localize_view_to_reconstruction.h"
#include "theia/sfm/match_and_verify_features.h"
#include "theia/sfm/nonlinear_reconstruction_estimator.h"
#include "theia/sfm/pose/compute_triplet_baseline_ratios.h"
#include "theia/sfm/pose/dls_impl.h"
#include "theia/sfm/pose/dls_pnp.h"
#include "theia/sfm/pose/eight_point_fundamental_matrix.h"
#include "theia/sfm/pose/essential_matrix_utils.h"
#include "theia/sfm/pose/estimate_positions_linear.h"
#include "theia/sfm/pose/estimate_positions_nonlinear.h"
#include "theia/sfm/pose/estimate_rotations_nonlinear.h"
#include "theia/sfm/pose/estimate_rotations_robust.h"
#include "theia/sfm/pose/five_point_focal_length_radial_distortion.h"
#include "theia/sfm/pose/five_point_relative_pose.h"
#include "theia/sfm/pose/four_point_focal_length.h"
#include "theia/sfm/pose/four_point_focal_length_helper.h"
#include "theia/sfm/pose/four_point_homography.h"
#include "theia/sfm/pose/four_point_relative_pose_partial_rotation.h"
#include "theia/sfm/pose/fundamental_matrix_util.h"
#include "theia/sfm/pose/pairwise_rotation_error.h"
#include "theia/sfm/pose/pairwise_translation_error.h"
#include "theia/sfm/pose/perspective_three_point.h"
#include "theia/sfm/pose/seven_point_fundamental_matrix.h"
#include "theia/sfm/pose/sim_transform_partial_rotation.h"
#include "theia/sfm/pose/test_util.h"
#include "theia/sfm/pose/three_point_relative_pose_partial_rotation.h"
#include "theia/sfm/pose/util.h"
#include "theia/sfm/pose_error.h"
#include "theia/sfm/reconstruction.h"
#include "theia/sfm/reconstruction_builder.h"
#include "theia/sfm/reconstruction_estimator.h"
#include "theia/sfm/reconstruction_estimator_options.h"
#include "theia/sfm/reconstruction_estimator_utils.h"
#include "theia/sfm/set_camera_intrinsics_from_priors.h"
#include "theia/sfm/track.h"
#include "theia/sfm/track_builder.h"
#include "theia/sfm/transformation/align_point_clouds.h"
#include "theia/sfm/transformation/align_reconstructions.h"
#include "theia/sfm/transformation/align_rotations.h"
#include "theia/sfm/transformation/gdls_similarity_transform.h"
#include "theia/sfm/transformation/transform_reconstruction.h"
#include "theia/sfm/triangulation/triangulation.h"
#include "theia/sfm/twoview_info.h"
#include "theia/sfm/types.h"
#include "theia/sfm/verify_two_view_matches.h"
#include "theia/sfm/view.h"
#include "theia/sfm/view_graph/orientations_from_view_graph.h"
#include "theia/sfm/view_graph/remove_disconnected_view_pairs.h"
#include "theia/sfm/view_graph/triplet_extractor.h"
#include "theia/sfm/view_graph/view_graph.h"
#include "theia/solvers/arrsac.h"
#include "theia/solvers/estimator.h"
#include "theia/solvers/evsac.h"
#include "theia/solvers/evsac_sampler.h"
#include "theia/solvers/inlier_support.h"
#include "theia/solvers/mle_quality_measurement.h"
#include "theia/solvers/prosac.h"
#include "theia/solvers/prosac_sampler.h"
#include "theia/solvers/quality_measurement.h"
#include "theia/solvers/random_sampler.h"
#include "theia/solvers/ransac.h"
#include "theia/solvers/sample_consensus_estimator.h"
#include "theia/solvers/sampler.h"
#include "theia/util/filesystem.h"
#include "theia/util/hash.h"
#include "theia/util/map_util.h"
#include "theia/util/mutable_priority_queue.h"
#include "theia/util/random.h"
#include "theia/util/stringprintf.h"
#include "theia/util/threadpool.h"
#include "theia/util/timer.h"
#include "theia/util/util.h"

#endif  // THEIA_THEIA_H_
