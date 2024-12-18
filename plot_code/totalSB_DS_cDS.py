import numpy as np
import sys
import inspect
import os
import matplotlib.pyplot as plt  # Ensure plt is imported here

# Get the current directory and set up the path for readResults
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0, "/user/home/ms23570/work/DaRT_RBE/DNA_damage/Clustering")

from readResults import *

def plotResults(numslices_start, numslices_end, marker, ax, markersize=0.3):
    # Initialize lists for storing results
    distances = []
    totalDSB = []
    totalSSB = []
    totalcDSB = []
    
    errors_DSB = []
    errors_SSB = []
    errors_cDSB = []
    
    SB_types = ["SSBtotal", "DSBtotal", "TotalSBtotal"]
    breaks_per_dose_all = []
    breaks_per_dose_all_cDSB = []

    # Loop through the specified range, but only process 1–25 and 100–125
    for i in range(numslices_start, numslices_end):
        if not (-39 <= i <= 0 or 1 <= i <= 39):  # Skip indices outside 1–25 and 100–125
            continue

        # # File paths for all particles and cDSB files
        # csv_files_all = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_copy_{i}_6Dec_100k_DF.csv",
        #                  f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_copy_{i}_6Dec_100k_1_DF.csv",
        #                  f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/example_simulation_DNA_copy_{i}_6Dec_100k_2_DF.csv"]
            
        # csv_file_all_cDSB = [f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/DSBclusterSize_example_simulation_DNA_copy_{i}_6Dec_100k_DF.csv",
        #                    f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/DSBclusterSize_example_simulation_DNA_copy_{i}_6Dec_100k_1_DF.csv",
        #                    f"/user/home/ms23570/work/AlphaGlue/sim_alpha_project/build/csv_file/DSBclusterSize_example_simulation_DNA_copy_{i}_6Dec_100k_2_DF.csv"]

        csv_files_all = [f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_copy_{i}_16Dec_30k_DF.csv"]
                        #  f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_copy_{i}_16Dec_30k_1_DF.csv",
                        #  f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/example_simulation_DNA_copy_{i}_16Dec_30k_2_DF.csv"]
        
        csv_file_all_cDSB = [f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_copy_{i}_16Dec_30k_DF.csv"]
                        #    f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_copy_{i}_16Dec_30k_1_DF.csv",
                        #    f"/user/home/ms23570/work/AlphaGlue/csv_file_At211_4µ_30k_39layars_5gab/DSBclusterSize_example_simulation_DNA_copy_{i}_16Dec_30k_2_DF.csv"]

        # Read datasets from CSV files
        dataset_all = [readIN(file) for file in csv_files_all]
        dataset_all_cDSB = [readIN(file) for file in csv_file_all_cDSB]

        # Lists to store breaks for all files
        breaks_all = []
        breaks_all_cDSB = []

        # Calculate breaks for each type (SSB, DSB, TotalSB) and add to breaks_all
        for SBtype in SB_types:
            breaks = [calcBreaks(SBtype, dataset) for dataset in dataset_all]
            breaks_all.append(np.mean(breaks))  # Average for current slice
        
        breaks_per_dose_all.append(breaks_all)  # Append breaks for each SB type

        # Calculate breaks for cDSB and add to breaks_all_cDSB
        breaks_cDSB = [calcComplexDSB("Total", dataset) for dataset in dataset_all_cDSB]
        breaks_per_dose_all_cDSB.append(np.mean(breaks_cDSB))  # Average for current slice

        # Calculate DSB, SSB, and cDSB totals
        totalDSB.append(breaks_all[1])  # DSB is the second element
        totalSSB.append(breaks_all[0])  # SSB is the first element
        totalcDSB.append(breaks_per_dose_all_cDSB[-1])  # Latest cDSB entry

        # Calculate errors (standard deviation) for DSB, SSB, and cDSB
        errors_DSB.append(np.std(breaks))
        errors_SSB.append(np.std(breaks))
        errors_cDSB.append(np.std(breaks_cDSB))

          # Calculate distance for plotting
        if i == 0:  # For upper tissue
            distance = (-(i + 1) * 0.005 + 10) - 10.04 ##it work for the 0 
        elif i > 0:  # For upper tissue
            distance = (i  * 0.005 - 10) + 10.04
        else:## if the i = -number under
            distance = (i * 0.005 + 10 - 0.005) - 10.04
              
        distances.append(distance)
    # # Plotting combined results with error bars
    # ax.errorbar(distances, totalDSB, yerr=errors_DSB, fmt='x', color='black', markersize=markersize*10, label='DSBtotal', capsize=5)
    # ax.errorbar(distances, totalSSB, yerr=errors_SSB, fmt='x', color='red', markersize=markersize*10, label='SSBtotal', capsize=5)
    # ax.errorbar(distances, totalcDSB, yerr=errors_cDSB, fmt='x', color='blue', markersize=markersize*10, label='cDSBtotal', capsize=5)

    # ax.set_xlabel('Distance (um) Y')
    # ax.set_ylabel('Number of Strand Breaks')
    # ax.set_title('DSB, SSB and cDSB vs Distance')

    # # Adjusting the legend
    # ax.legend(loc='upper right', fontsize='x-small', frameon=False, ncol=1, borderpad=0.3,
    #           labelspacing=0.2, handletextpad=0.1, bbox_to_anchor=(1, 1))
    # ax.grid()
        # Plotting combined results with error bars
    ax.errorbar(distances, totalDSB, yerr=errors_DSB, fmt='x', color='black', markersize=markersize*10, label='DSBtotal', capsize=5)
    ax.errorbar(distances, totalSSB, yerr=errors_SSB, fmt='x', color='red', markersize=markersize*10, label='SSBtotal', capsize=5)
    # ax.errorbar(distances, totalcDSB, yerr=errors_cDSB, fmt='x', color='blue', markersize=markersize*10, label='cDSBtotal', capsize=5)

    # Set logarithmic scale on y-axis
    # ax.set_yscale('log')

    ax.set_xlabel('Distance (um) Y')
    ax.set_ylabel('Number of Strand Breaks')
    ax.set_title('DSB, SSB and cDSB vs Distance (Logarithmic Scale)')

   # Adjusting the legend
    ax.legend(loc='upper right', fontsize='x-small', frameon=False, ncol=1, borderpad=0.3,
          labelspacing=0.2, handletextpad=0.1, bbox_to_anchor=(1, 1))
    ax.grid()
    # ax.set_ylim(0,300)## to limte the y axis

    

# Example usage
fig, ax = plt.subplots()

# Now, only data from 1 to 25 and 100 to 125 will be processed
plotResults(-100, 100, 'x', ax, markersize=0.3)

# Save the combined plot
plt.savefig("DSB_SSB_vs_distance_with_error.png")
