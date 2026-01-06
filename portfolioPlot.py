import matplotlib.pyplot as plt
import numpy as np

def read_histogram_data(filename):
    centres = []
    counts = []
    try:
        with open(filename, 'r') as f:
            for line in f:
                parts = line.strip().split(',')
                
                #3 columns: Index, Centre, Count
                if len(parts) >= 3:
                    centres.append(float(parts[1])) # Column 1 is Centre
                    counts.append(float(parts[2]))  # Column 2 is Count
    except FileNotFoundError:
        print(f"Error: Could not find {filename}")
        return None, None
    
    return np.array(centres), np.array(counts)

def plot_all_distributions():
    files = {
        'Independent': 'independent.txt',
        'Correlation 1': 'first_correlation.txt',
        'Correlation 2': 'second_correlation.txt'
    }

    plt.figure(figsize=(10, 6))
    

    colours = ['blue', 'green', 'red']
    
    for (label, filename), colour in zip(files.items(), colours):
        centres, counts = read_histogram_data(filename)
        
        if centres is not None and counts is not None:
            # Normalize counts to Probability Density for fair comparison
            if len(centres) > 1:
                bin_width =    centres[1] -      centres[0]
                density = counts / (np.sum(counts) * bin_width)
            else:
                density = counts # Fallback if only 1 bin

            plt.plot(centres, density, label=label, color=colour, linewidth=2, linestyle='-')
            plt.fill_between(centres, density, alpha=0.1, color=colour)

    plt.title('Portfolio Value Distributions (Comparison)')
    plt.xlabel('Portfolio Value')
    plt.ylabel('Probability Density')
    plt.legend()
    plt.grid(True, which='both', linestyle='--', alpha=0.5)
    plt.savefig('portfolio_comparison.png')
    plt.show()

if __name__ == "__main__":
    plot_all_distributions()