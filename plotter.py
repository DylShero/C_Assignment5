import matplotlib.pyplot as plt
import numpy as np
import sys

# Program to plot histogram data from assignment 5a 

# Define the filename 
filename = "normal_histogram.txt"  

try:
    # Load the data
    # The C code outputs comma separated: index, bin_center, bin_count

    data = np.loadtxt(filename, delimiter=',')

    #Extract columns
    bin_centers = data[:, 1]
    bin_counts  = data[:, 2]

    # Calculate Bar Width
    if len(bin_centers) > 1:
        bin_width = bin_centers[1] - bin_centers[0]
    else:
        bin_width = 1.0 # If only one bin exists

    # Create the Plot
    plt.figure(figsize=(10, 6))
    plt.bar(bin_centers, bin_counts, width=bin_width, align='center', edgecolor='black', alpha=0.7)
    plt.xlabel('Value (Bin Centers)')
    plt.ylabel('Frequency (Counts)')
    plt.title('Histogram Data')
    plt.grid(axis='y', alpha=0.5)
    plt.savefig("normal_histogram_plot.png")
    plt.show()

except OSError:
    print(f"Error could not find or open file '{filename}'.")
except Exception as e:
    print(f"error occurred: {e}")