import numpy as np
import sys
import inspect
import os
import matplotlib.pyplot as plt

currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0, "/user/home/ms23570/work/DaRT_RBE/DNA_damage/Clustering")

from readResults import *

def plotResults(numslices_start, numslices_end, marker, ax, markersize=4):
    # Initialize lists for storing results
    distances = []
    doses_all_particles = []
    doses_alpha_particles = []
    doses_electron_particles = []
    doses_gamma_particles = []
    errors_all_particles = []
    errors_alpha_particles = []
    errors_electron_particles = []
    errors_gamma_particles = []

    # Loop through the specified range, but only process 1–25 and 100–125
    for i in range(numslices_start, numslices_end):
        if not (-389 <= i <= 0 or 1 <= i <= 390):
            continue

        # File names for all particles and alpha particles (including the extra files)
        csv_files_all = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_copy_{i}_6Dec_100k_DF.csv",
                         f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_copy_{i}_6Dec_100k_1_DF.csv",
                         f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_copy_{i}_6Dec_100k_2_DF.csv"]
        
        csv_files_alpha = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_alpha_copy_{i}_6Dec_100k_DF.csv",
                           f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_alpha_copy_{i}_6Dec_100k_1_DF.csv",
                           f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_alpha_copy_{i}_6Dec_100k_2_DF.csv"]
        
        csv_files_electron = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_electron_copy_{i}_6Dec_100k_DF.csv",
                              f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_electron_copy_{i}_6Dec_100k_1_DF.csv",
                              f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_electron_copy_{i}_6Dec_100k_2_DF.csv"]

        
        csv_files_gamma = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_gamma_copy_{i}_6Dec_100k_DF.csv",
                          f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_gamma_copy_{i}_6Dec_100k_1_DF.csv",
                          f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_gamma_copy_{i}_6Dec_100k_2_DF.csv"]


        # csv_files_alpha = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_alpha_copy_{i}_10Dec_30k_DF.csv",
        #                    f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_alpha_copy_{i}_10Dec_30k_1_DF.csv",
        #                    f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_alpha_copy_{i}_10Dec_30k_2_DF.csv"]
                           
        

        # csv_files_electron = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_electron_copy_{i}_10Dec_30k_DF.csv",
        #                       f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_electron_copy_{i}_10Dec_30k_1_DF.csv",
        #                       f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_electron_copy_{i}_10Dec_30k_2_DF.csv"]

        # csv_files_gamma = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_gamma_copy_{i}_10Dec_30k_DF.csv",
        #                   f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_gamma_copy_{i}_10Dec_30k_1_DF.csv",
        #                   f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_gamma_copy_{i}_10Dec_30k_2_DF.csv"]
        
        # csv_files_all = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_copy_{i}_10Dec_30k_DF.csv",
        #                  f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_copy_{i}_10Dec_30k_1_DF.csv",
        #                  f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_half/example_simulation_DNA_copy_{i}_10Dec_30k_2_DF.csv"]
        
        
        # csv_files_alpha = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_alpha_copy_{i}_12Dec_100k_DF.csv",
        #                    f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_alpha_copy_{i}_12Dec_100k_1_DF.csv",
        #                    f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_alpha_copy_{i}_12Dec_100k_2_DF.csv"]
                           
        

        # csv_files_electron = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_electron_copy_{i}_12Dec_100k_DF.csv",
        #                       f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_electron_copy_{i}_12Dec_100k_1_DF.csv",
        #                       f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_electron_copy_{i}_12Dec_100k_2_DF.csv"]

        # csv_files_gamma = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_gamma_copy_{i}_12Dec_100k_DF.csv",
        #                   f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_gamma_copy_{i}_12Dec_100k_1_DF.csv",
        #                   f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_gamma_copy_{i}_12Dec_100k_2_DF.csv"]
        
        # csv_files_all = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_copy_{i}_12Dec_100k_DF.csv",
        #                  f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_copy_{i}_12Dec_100k_1_DF.csv",
        #                  f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_0p15nm_100k_39layars/example_simulation_DNA_copy_{i}_12Dec_100k_2_DF.csv"]

        # csv_files_alpha = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_alpha_copy_{i}_11Dec_100k_DF.csv",
        #                    f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_alpha_copy_{i}_11Dec_100k_1_DF.csv",
        #                    f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_alpha_copy_{i}_11Dec_100k_2_DF.csv"]
                           
        

        # csv_files_electron = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_electron_copy_{i}_11Dec_100k_DF.csv",
        #                       f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_electron_copy_{i}_11Dec_100k_1_DF.csv",
        #                       f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_electron_copy_{i}_11Dec_100k_2_DF.csv"]

        # csv_files_gamma = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_gamma_copy_{i}_11Dec_100k_DF.csv",
        #                   f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_gamma_copy_{i}_11Dec_100k_1_DF.csv",
        #                   f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_gamma_copy_{i}_11Dec_100k_2_DF.csv"]
        
        # csv_files_all = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_copy_{i}_11Dec_100k_DF.csv",
        #                  f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_copy_{i}_11Dec_100k_1_DF.csv",
        #                  f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/csv_file_4µm_100k/example_simulation_DNA_copy_{i}_11Dec_100k_2_DF.csv"]

        # Read datasets for each type of particle
        dataset_all = [readIN(file) for file in csv_files_all]
        dataset_alpha = [readIN(file) for file in csv_files_alpha]
        dataset_e = [readIN(file) for file in csv_files_electron]
        dataset_gamma = [readIN(file) for file in csv_files_gamma]

        # Calculate doses for each dataset using the calculateDose function
        totalDose_all = np.mean([calculateDose(d) for d in dataset_all])
        totalDose_alpha = np.mean([calculateDose(d) for d in dataset_alpha])
        totalDose_electron = np.mean([calculateDose(d) for d in dataset_e])
        totalDose_gamma = np.mean([calculateDose(d) for d in dataset_gamma])

        # Calculate errors (standard deviation across the datasets)
        error_all = np.std([calculateDose(d) for d in dataset_all])
        error_alpha = np.std([calculateDose(d) for d in dataset_alpha])
        error_electron = np.std([calculateDose(d) for d in dataset_e])
        error_gamma = np.std([calculateDose(d) for d in dataset_gamma])

        # Store the calculated doses and errors
        doses_all_particles.append(totalDose_all)
        doses_alpha_particles.append(totalDose_alpha)
        doses_electron_particles.append(totalDose_electron)
        doses_gamma_particles.append(totalDose_gamma)

        errors_all_particles.append(error_all)
        errors_alpha_particles.append(error_alpha)
        errors_electron_particles.append(error_electron)
        errors_gamma_particles.append(error_gamma)

          # Calculate distance for plotting
        if i == 0:  # For upper tissue
            distance = (-(i + 1) * 0.05 + 10) - 10.04 ##it work for the 0 
        elif i > 0:  # For upper tissue
            distance = (i  * 0.05 - 10) + 10.04
        else:## if the i = -number under
            distance = (i * 0.05 + 10 - 0.05) - 10.04
              
        distances.append(distance)

    # Plotting dose vs. distance for both groups, including error bars
    ax.errorbar(distances, doses_all_particles, yerr=errors_all_particles, fmt='x', color='orange', 
                markersize=markersize, label='All Dose (Gy)', capsize=5)
    ax.errorbar(distances, doses_alpha_particles, yerr=errors_alpha_particles, fmt='x', color='red', 
                markersize=markersize, label='Alpha Dose (Gy)', capsize=5)
    ax.errorbar(distances, doses_electron_particles, yerr=errors_electron_particles, fmt='x', color='blue', 
                markersize=markersize, label='Electron Dose (Gy)', capsize=5)
    ax.errorbar(distances, doses_gamma_particles, yerr=errors_gamma_particles, fmt='x', color='green', 
                markersize=markersize, label='Gamma Dose (Gy)', capsize=5)

    # Set labels, title, and legend
    ax.set_xlabel('Distance (mm) Y')
    ax.set_ylabel('Dose (Gy)')
    ax.set_title('Dose vs Distance for alpha, electron and gamma')

    ax.legend(loc='upper right', fontsize='x-small', frameon=False, ncol=1, borderpad=0.3,
              labelspacing=0.1, handletextpad=0.1, bbox_to_anchor=(1, 1))
    ax.grid()
    # ax.set_ylim(0,80000)## to limte the y axis
    # ax.set_ylim(0,3000)## to limte the y axis



# Example usage
fig, ax = plt.subplots()

# Only data from 1 to 25 and 100 to 125 will be processed
plotResults(-40, 40, 'x', ax, markersize=4) 

# Save the plot
plt.savefig("Dose_vs_distance_with_error_4µm.png")
