import numpy as np
import sys
import inspect
import os
import matplotlib.pyplot as plt  # Ensure plt is imported here

currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0,"/user/home/ms23570/work/DaRT_RBE/DNA_damage/Clustering")

from readResults import *

def plotResults(numslices_start, numslices_end, marker, ax, markersize=0.3):
    distances = []
    # Separate lists for each particle type
    SSBalpha, DSBalpha, cDSBalpha = [], [], []
    SSBe, DSBe, cDSBe = [], [], []
    SSBgamma, DSBgamma, cDSBgamma = [], [], []

    # Separate error lists for each particle type
    errors_SSBalpha, errors_DSBalpha, errors_cDSBalpha = [], [], []
    errors_SSBe, errors_DSBe, errors_cDSBe = [], [], []
    errors_SSBgamma, errors_DSBgamma, errors_cDSBgamma = [], [], []

    SB_types = ["SSBtotal", "DSBtotal", "TotalSBtotal"]

    for i in range(numslices_start, numslices_end):
        if not (-14 <= i <= 0 or 1 <= i <= 8):
            continue

        # # Define the file paths for each of the datasets, including three `dataset_all` files
        # csv_files_alpha = [f"/user/home/ms23570/work/AlphaGlue/build/csv_file/example_simulation_DNA_alpha_copy_{i}_6Dec_100k_DF.csv",
        #                    f"/user/home/ms23570/work/AlphaGlue/build/csv_file/example_simulation_DNA_alpha_copy_{i}_6Dec_100k_1_DF.csv",
        #                    f"/user/home/ms23570/work/AlphaGlue/build/csv_file/example_simulation_DNA_alpha_copy_{i}_6Dec_100k_2_DF.csv"]
        
        # csv_files_electron = [f"/user/home/ms23570/work/AlphaGlue/build/csv_file/example_simulation_DNA_electron_copy_{i}_6Dec_100k_DF.csv",
        #                       f"/user/home/ms23570/work/AlphaGlue/build/csv_file/example_simulation_DNA_electron_copy_{i}_6Dec_100k_1_DF.csv",
        #                       f"/user/home/ms23570/work/AlphaGlue/build/csv_file/example_simulation_DNA_electron_copy_{i}_6Dec_100k_2_DF.csv"]

        
        # csv_files_gamma = [f"/user/home/ms23570/work/AlphaGlue/build/csv_file/example_simulation_DNA_gamma_copy_{i}_6Dec_100k_DF.csv",
        #                   f"/user/home/ms23570/work/AlphaGlue/csv_file/example_simulation_DNA_gamma_copy_{i}_6Dec_100k_1_DF.csv",
        #                   f"/user/home/ms23570/work/AlphaGlue/csv_file/example_simulation_DNA_gamma_copy_{i}_6Dec_100k_2_DF.csv"]

        csv_files_alpha = [f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_alpha_copy_{i}_16Dec_30k_DF.csv",
                           f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_alpha_copy_{i}_16Dec_30k_1_DF.csv",
                           f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_alpha_copy_{i}_16Dec_30k_2_DF.csv"]
                           
        

        csv_files_electron = [f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_electron_copy_{i}_16Dec_30k_DF.csv",
                              f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_electron_copy_{i}_16Dec_30k_1_DF.csv",
                              f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_electron_copy_{i}_16Dec_30k_2_DF.csv"]

        csv_files_gamma = [f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_gamma_copy_{i}_16Dec_30k_DF.csv",
                          f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_gamma_copy_{i}_16Dec_30k_1_DF.csv",
                          f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_gamma_copy_{i}_16Dec_30k_2_DF.csv"]
        
        csv_files_all = [f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_copy_{i}_16Dec_30k_DF.csv",
                         f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_copy_{i}_16Dec_30k_1_DF.csv",
                         f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_copy_{i}_16Dec_30k_2_DF.csv"]
        
        csv_files_alphacDSB = [f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_alpha_copy_{i}_16Dec_30k_DF.csv",
                               f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_alpha_copy_{i}_16Dec_30k_1_DF.csv",
                               f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_alpha_copy_{i}_16Dec_30k_2_DF.csv"]

        csv_files_electroncDSB = [f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_electron_copy_{i}_16Dec_30k_DF.csv",
                                  f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_electron_copy_{i}_16Dec_30k_1_DF.csv",
                                  f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_electron_copy_{i}_16Dec_30k_2_DF.csv"]

        csv_files_gammacDSB = [f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_gamma_copy_{i}_16Dec_30k_DF.csv",
                               f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_gamma_copy_{i}_16Dec_30k_1_DF.csv",
                               f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_gamma_copy_{i}_16Dec_30k_2_DF.csv"]
                               

  
        
        

        # Define paths for `cDSB` files
        # csv_files_alphacDSB = [f"/user/home/ms23570/work/AlphaGlue/csv_file/DSBclusterSize_example_simulation_DNA_alpha_copy_{i}_6Dec_100k_DF.csv",
        #                        f"/user/home/ms23570/work/AlphaGlue/csv_file/DSBclusterSize_example_simulation_DNA_alpha_copy_{i}_6Dec_100k_1_DF.csv",
        #                        f"/user/home/ms23570/work/AlphaGlue/csv_file/DSBclusterSize_example_simulation_DNA_alpha_copy_{i}_6Dec_100k_2_DF.csv"]

        # csv_files_electroncDSB = [f"/user/home/ms23570/work/AlphaGlue/csv_file/DSBclusterSize_example_simulation_DNA_electron_copy_{i}_6Dec_100k_DF.csv",
        #                           f"/user/home/ms23570/work/AlphaGlue/csv_file/DSBclusterSize_example_simulation_DNA_electron_copy_{i}_6Dec_100k_1_DF.csv",
        #                           f"/user/home/ms23570/work/AlphaGlue/csv_file/DSBclusterSize_example_simulation_DNA_electron_copy_{i}_6Dec_100k_2_DF.csv"]

        # csv_files_gammacDSB = [f"/user/home/ms23570/work/AlphaGlue/csv_file/DSBclusterSize_example_simulation_DNA_gamma_copy_{i}_6Dec_100k_DF.csv",
        #                        f"/user/home/ms23570/work/AlphaGlue/csv_file/DSBclusterSize_example_simulation_DNA_gamma_copy_{i}_6Dec_100k_1_DF.csv",
        #                        f"/user/home/ms23570/work/AlphaGlue/csv_file/DSBclusterSize_example_simulation_DNA_gamma_copy_{i}_6Dec_100k_2_DF.csv"]
                               

        # csv_files_all = [f"/user/home/ms23570/work/AlphaGlue/csv_file/example_simulation_DNA_copy_{i}_6Dec_100k_DF.csv",
        #                  f"/user/home/ms23570/work/AlphaGlue/csv_file/example_simulation_DNA_copy_{i}_6Dec_100k_1_DF.csv",
        #                  f"/user/home/ms23570/work/AlphaGlue/csv_file/example_simulation_DNA_copy_{i}_6Dec_100k_2_DF.csv"]

        # print(f"Reading files for slice {i} - Alpha, Electron, Gamma, and All Doses")

        dataset_alpha = [readIN(file) for file in csv_files_alpha]
        dataset_electron = [readIN(file) for file in csv_files_electron]
        dataset_gamma = [readIN(file) for file in csv_files_gamma]
        dataset_all = [readIN(file) for file in csv_files_all]  # Read all `dataset_all` files

        # Read the cDSB datasets
        dataset_alphacDSB = [readIN(file) for file in csv_files_alphacDSB]
        dataset_electroncDSB = [readIN(file) for file in csv_files_electroncDSB]
        dataset_gammacDSB = [readIN(file) for file in csv_files_gammacDSB]

        breaks_per_dose_alpha, breaks_per_dose_electron, breaks_per_dose_gamma = [], [], []
        complex_dsb_alpha, complex_dsb_electron, complex_dsb_gamma = [], [], []

        for SBtype in SB_types:
            breaks_alpha = [calcBreaks(SBtype, dataset_alpha[d]) / calculateDose(dataset_all[d])/ (301220 * 1e-9) for d in range(len(dataset_alpha)) ]
            breaks_electron = [calcBreaks(SBtype, dataset_electron[d]) /calculateDose(dataset_all[d])/ (301220 * 1e-9) for d in range(len(dataset_electron)) ]
            breaks_gamma = [calcBreaks(SBtype, dataset_gamma[d]) /calculateDose(dataset_all[d])/ (301220 * 1e-9) for d in range(len(dataset_gamma)) ]
            
            breaks_per_dose_alpha.append(breaks_alpha)
            breaks_per_dose_electron.append(breaks_electron)
            breaks_per_dose_gamma.append(breaks_gamma)

        # Calculate cDSB for each particle type, normalized by the dose
        complex_dsb_alpha = [calcComplexDSB("Total", dataset_alphacDSB[d]) / calculateDose(dataset_all[d])/ (301220 * 1e-9) for d in range(len(dataset_alphacDSB)) ]
        complex_dsb_electron = [calcComplexDSB("Total", dataset_electroncDSB[d]) /calculateDose(dataset_all[d])/ (301220 * 1e-9) for d in range(len(dataset_electroncDSB)) ]
        complex_dsb_gamma = [calcComplexDSB("Total", dataset_gammacDSB[d]) / calculateDose(dataset_all[d])/ (301220 * 1e-9) for d in range(len(dataset_gammacDSB)) ]

        # Appending SSB, DSB, and cDSB values for each particle type
        SSBalpha.append(np.mean(breaks_per_dose_alpha[0]))
        DSBalpha.append(np.mean(breaks_per_dose_alpha[1]))
        cDSBalpha.append(np.mean(complex_dsb_alpha))

        SSBe.append(np.mean(breaks_per_dose_electron[0]))
        DSBe.append(np.mean(breaks_per_dose_electron[1]))
        cDSBe.append(np.mean(complex_dsb_electron))

        SSBgamma.append(np.mean(breaks_per_dose_gamma[0]))
        DSBgamma.append(np.mean(breaks_per_dose_gamma[1]))
        cDSBgamma.append(np.mean(complex_dsb_gamma))

        # Error estimates for each particle type and strand break type
        errors_SSBalpha.append(np.std(breaks_per_dose_alpha[0]))
        errors_DSBalpha.append(np.std(breaks_per_dose_alpha[1]))
        errors_cDSBalpha.append(np.std(complex_dsb_alpha))

        errors_SSBe.append(np.std(breaks_per_dose_electron[0]))
        errors_DSBe.append(np.std(breaks_per_dose_electron[1]))
        errors_cDSBe.append(np.std(complex_dsb_electron))

        errors_SSBgamma.append(np.std(breaks_per_dose_gamma[0]))
        errors_DSBgamma.append(np.std(breaks_per_dose_gamma[1]))
        errors_cDSBgamma.append(np.std(complex_dsb_gamma))

          # Calculate distance for plotting
        if i == 0:  # For upper tissue
            distance = (-(i + 1) * 0.5 + 10) - 10.04 ##it work for the 0 
        elif i > 0:  # For upper tissue
            distance = (i  * 0.5 - 10) + 10.04
        else:## if the i = -number under
            distance = (i * 0.5 + 10 - 0.5) - 10.04
              
        distances.append(distance)
        # print(f"Slice {i}: Distance = {(i * 0.05 + 10 - 0.05)}")
    # Plotting results with error bars for each type of strand break for all particle types
    # ax.errorbar(distances, SSBalpha, yerr=errors_DSBalpha, fmt='x', color='blue', markersize=markersize, label='SSB_alpha', capsize=5)

    ax.errorbar(distances, DSBalpha, yerr=errors_DSBalpha, fmt='x', color='blue', markersize=markersize, label='DSB_alpha', capsize=5)
    # ax.errorbar(distances, cDSBalpha, yerr=errors_cDSBalpha, fmt='x', color='blue', markersize=markersize, label='cDSB_alpha', capsize=5)

    # ax.errorbar(distances, SSBe, yerr=errors_SSBe, fmt='x', color='red', markersize=markersize, label='SSB_electron', capsize=5)
    ax.errorbar(distances, DSBe, yerr=errors_DSBe, fmt='x', color='red', markersize=markersize, label='DSB_electron', capsize=5)
    # ax.errorbar(distances, cDSBe, yerr=errors_cDSBe, fmt='x', color='red', markersize=markersize, label='cDSB_electron', capsize=5)
    
    # ax.errorbar(distances, SSBgamma, yerr=errors_DSBgamma, fmt='x', color='green', markersize=markersize, label='SSB_gamma', capsize=5)
    # ax.errorbar(distances, DSBgamma, yerr=errors_DSBgamma, fmt='x', color='green', markersize=markersize, label='DSB_gamma', capsize=5)
    # ax.errorbar(distances, cDSBgamma, yerr=errors_cDSBgamma, fmt='x', color='green', markersize=markersize, label='cDSB_gamma', capsize=5)

    ax.set_xlabel('Distance (mm) Y')
    ax.set_ylabel('Number of DSB Gy$^{-1}$ Gbp$^{-1}$')
    ax.set_title('DSB for Alpha, Electron, and Gamma vs Distance')

    ax.legend(loc='upper right', fontsize='x-small', frameon=False, ncol=1, borderpad=0.3,
              labelspacing=0.2, handletextpad=0.1, bbox_to_anchor=(1, 1))
    ax.grid()
    # ax.set_ylim(0,20)## to limte the y axis

# Example usage
fig, ax = plt.subplots()
plotResults(-39, 39, 'x', ax, markersize=4)
plt.savefig("cDSB_with_error.png")
