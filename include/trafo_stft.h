#ifndef TRAFO_STFT_H
#define TRAFO_STFT_H

#include <fftw3.h>
#include <math.h>
#include <stdlib.h>

#include "pad.h"
#include "window.h"
#include "signal.h"

/**
 * @brief Structure for STFT (Short-Time Fourier Transform) parameters and plans.
 */
typedef struct {
    int win;                  /**< Window size. */
    int hop;                  /**< Hop size. */
    int nfft;                 /**< Number of FFT points. */
    fftwf_plan plan;          /**< FFTW plan for STFT computation. */
    float* stft_in;           /**< Input array for STFT computation. */
    fftwf_complex* stft_out;  /**< Output array for STFT computation. */
    float *wnd;               /**< Hanning window array. */
    Padding* padding;         /**< Pointer to the padding information. */
} StftStruct;

/**
 * @brief Initialize the STFT structure.
 *
 * @param stft_struct Pointer to the STFT structure to initialize.
 * @param n_fft Length of the FFT.
 * @param win_length Length of the window.
 * @param hop_length Length of the hop.
 * @param padding Pointer to the padding information.
 */
void stft_init(StftStruct *stft_struct, int n_fft, int win_length, int hop_length, Padding* padding);

/**
 * @brief Compute the STFT (Short-Time Fourier Transform) for a given signal.
 *
 * @param stft_struct Pointer to the STFT structure.
 * @param channel_signal Pointer to the input signal.
 * @param num_bins Number of bins in the FFT.
 * @param do_pad Flag indicating whether padding should be applied.
 * @return Pointer to the computed STFT result.
 */
fftwf_complex* stft_compute(StftStruct* stft_struct, Signal *channel_signal, int num_bins, int do_pad);

/**
 * @brief Inner function to compute the STFT.
 *
 * @param stft_struct Pointer to the STFT structure.
 * @param signal Pointer to the input signal.
 * @param stft_result Pointer to store the computed STFT result.
 * @param num_frames Number of frames.
 * @param num_bins Number of bins.
 */
void stft_inner(StftStruct* stft_struct, float* signal, fftwf_complex** stft_result, int num_frames, int num_bins);

/**
 * @brief Clean up resources allocated for STFT.
 *
 * @param stft_struct Pointer to the STFT structure to clean up.
 */
void stft_clean(StftStruct *stft_struct);

#endif
