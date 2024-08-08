
import tkinter as tk
from tkinter import filedialog
import os
import ctypes
import sys
import subprocess

# Load the shared library
if os.name == 'nt':  # Windows
    compressor_lib = ctypes.CDLL('./compressor.dll')
elif os.name == 'posix':  # macOS and Linux
    if sys.platform == 'darwin':
        compressor_lib = ctypes.CDLL('./libcompressor.dylib')
    else:
        compressor_lib = ctypes.CDLL('./libcompressor.so')

# Declare the function prototypes
compress_file = compressor_lib.compress_file
compress_file.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
compress_file.restype = None

decompress_file = compressor_lib.decompress_file
decompress_file.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
decompress_file.restype = None

# Function to open the file in the system's file explorer
def open_file_in_explorer(file_path):
    if os.name == 'nt':  # Windows
        os.startfile(os.path.dirname(file_path))
    elif os.name == 'posix':  # macOS and Linux
        subprocess.call(['open' if sys.platform == 'darwin' else 'xdg-open', os.path.dirname(file_path)])

# Function to handle file selection and compression
def select_and_compress_file():
    file_path = filedialog.askopenfilename()
    if file_path:
        open_file_in_explorer(file_path)
        
        # Define the output file name by replacing the original extension with .bin
        base_name = os.path.splitext(file_path)[0]
        output_file = base_name + ".bin"

        # Call the C++ compression function
        compress_file(file_path.encode('utf-8'), output_file.encode('utf-8'))

        print(f'File compression initiated for: {file_path}')

# Function to handle file selection and decompression
def select_and_decompress_file():
    file_path = filedialog.askopenfilename()
    if file_path:
        open_file_in_explorer(file_path)
        
        # Define the output file name by replacing the .bin extension with _decompressed.txt
        base_name = os.path.splitext(file_path)[0]
        output_file = base_name + "_decompressed.txt"

        # Call the C++ decompression function
        decompress_file(file_path.encode('utf-8'), output_file.encode('utf-8'))

        print(f'File decompression initiated for: {file_path}')

# Main GUI setup
root = tk.Tk()
root.title("File Compressor and Decompressor")

frame = tk.Frame(root, width=300, height=200)
frame.pack(pady=20, padx=70)

compress_button = tk.Button(frame, text="Select File to Compress", command=select_and_compress_file)
compress_button.pack(pady=10 )

decompress_button = tk.Button(frame, text="Select File to Decompress", command=select_and_decompress_file)
decompress_button.pack(pady=10)

root.mainloop()
