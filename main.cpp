//
// author: 会飞的吴克
//
#include "dehaze.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

// Ori ver
/*int main(int argc, char** argv)
{
    __Assert__(argc == 2, "Please provide a correct image name.");
    std::string img_name = argv[1];
    int pos = img_name.find_last_of('/');
    std::string path;
    if (pos == std::string::npos) { path = ""; }
    else { path = img_name.substr(0, pos + 1); img_name = img_name.substr(pos + 1); }
    cv::Mat img = cv::imread(path + img_name);
    cv::Mat res = DarkChannel::dehaze(img);
    std::cout << res.rows << " " << res.cols << std::endl;
    cv::imwrite("dehazed_" + img_name, res);
    cv::imshow("result", res);
    cv::waitKey(0);
    return 0;
}*/

// Ver 2
/*int main(int argc, char** argv)
{
    try {
        __Assert__(argc == 2, "Please provide a correct image name.");
        std::string img_path = argv[1];

        // Use forward slashes consistently
        std::replace(img_path.begin(), img_path.end(), '\\', '/');

        // Extract filename from path
        size_t pos = img_path.find_last_of('/');
        std::string path = "";
        std::string img_name = img_path;

        if (pos != std::string::npos) {
            path = img_path.substr(0, pos + 1);
            img_name = img_path.substr(pos + 1);
        }

        // Debug output
        std::cout << "Processing image: " << path + img_name << std::endl;

        // Load image
        cv::Mat img = cv::imread(path + img_name);
        if (img.empty()) {
            std::cerr << "Error: Failed to load image: " << path + img_name << std::endl;
            return 1;
        }

        std::cout << "Image loaded successfully. Size: " << img.cols << "x" << img.rows << std::endl;

        // Process image
        cv::Mat res = DarkChannel::dehaze(img);
        std::cout << "Dehazing completed. Result size: " << res.rows << "x" << res.cols << std::endl;

        // Save and display result
        cv::imwrite("dehazed_" + img_name, res);
        std::cout << "Result saved as: dehazed_" << img_name << std::endl;

        cv::imshow("result", res);
        cv::waitKey(0);

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
}*/

#ifdef _WIN32
#include <Windows.h>
#include <commdlg.h>
#endif

// Function to show file open dialog (ANSI version)
std::string getImageFile() {
#ifdef _WIN32
    OPENFILENAMEA ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Image Files (*.jpg;*.jpeg;*.png;*.bmp)\0*.jpg;*.jpeg;*.png;*.bmp\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "jpg";

    if (GetOpenFileNameA(&ofn)) {
        return std::string(fileName);
    }
    return "";
#else
    // For non-Windows platforms, use simple input
    std::string filePath;
    std::cout << "Enter path to image file: ";
    std::getline(std::cin, filePath);
    return filePath;
#endif
}

/* int main(int argc, char** argv) {
    try {
        std::string img_path;

        // Check if image path is provided as command line argument
        if (argc > 1) {
            img_path = argv[1];
        }
        else {
            // If no command line argument, prompt user to select a file
            img_path = getImageFile();
            if (img_path.empty()) {
                std::cerr << "No image selected." << std::endl;
                return 1;
            }
        }

        // Use forward slashes consistently
        std::replace(img_path.begin(), img_path.end(), '\\', '/');

        // Extract filename from path
        size_t pos = img_path.find_last_of('/');
        std::string path = "";
        std::string img_name = img_path;

        if (pos != std::string::npos) {
            path = img_path.substr(0, pos + 1);
            img_name = img_path.substr(pos + 1);
        }

        // Debug output
        std::cout << "Processing image: " << path + img_name << std::endl;

        // Load image
        cv::Mat img = cv::imread(path + img_name);
        if (img.empty()) {
            std::cerr << "Error: Failed to load image: " << path + img_name << std::endl;
            return 1;
        }

        std::cout << "Image loaded successfully. Size: " << img.cols << "x" << img.rows << std::endl;

        // Process image
        cv::Mat res = DarkChannel::dehaze(img);
        std::cout << "Dehazing completed. Result size: " << res.rows << "x" << res.cols << std::endl;

        // Save and display result
        cv::imwrite("dehazed_" + img_name, res);
        std::cout << "Result saved as: dehazed_" << img_name << std::endl;

        cv::imshow("result", res);
        cv::waitKey(0);

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
}*/


// CAN RUN DE CODE
/*int main(int argc, char** argv) {
    try {
        std::string project_path = "C:/Users/esther/source/repos/Dehaze/";
        std::string img_path;

        // Check if image path is provided as command line argument
        if (argc > 1) {
            std::string arg_path = argv[1];

            // Check if the argument is a relative path
            if (arg_path.find(':') == std::string::npos) {
                // It's a relative path, combine with project path
                img_path = project_path + arg_path;
            }
            else {
                // It's an absolute path, use it directly
                img_path = arg_path;
            }
        }
        else {
            // No argument provided, use default
            img_path = project_path + "images/0001_0.8_0.2.jpg";
        }

        // Use forward slashes consistently
        std::replace(img_path.begin(), img_path.end(), '\\', '/');

        std::cout << "Processing image: " << img_path << std::endl;

        // Load image
        cv::Mat img = cv::imread(img_path);
        if (img.empty()) {
            std::cerr << "Error: Failed to load image: " << img_path << std::endl;
            return 1;
        }

        // Extract just the filename for the output file
        size_t pos = img_path.find_last_of('/');
        std::string img_name = (pos != std::string::npos) ? img_path.substr(pos + 1) : img_path;

        std::cout << "Image loaded successfully. Size: " << img.cols << "x" << img.rows << std::endl;

        // Process image
        cv::Mat res = DarkChannel::dehaze(img);
        std::cout << "Dehazing completed. Result size: " << res.rows << "x" << res.cols << std::endl;

        // Save in the project directory
        std::string output_path = project_path + "dehazed_" + img_name;
        cv::imwrite(output_path, res);
        std::cout << "Result saved as: " << output_path << std::endl;

        cv::imshow("result", res);
        cv::waitKey(0);

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
}*/



// can run de code ADD Asking Multiple Image/Loop
// Function to process a single image
bool processImage(const std::string& img_path, const std::string& project_path) {
    // Use forward slashes consistently
    std::string normalized_path = img_path;
    std::replace(normalized_path.begin(), normalized_path.end(), '\\', '/');

    std::cout << "Processing image: " << normalized_path << std::endl;

    // Load image
    cv::Mat img = cv::imread(normalized_path);
    if (img.empty()) {
        std::cerr << "Error: Failed to load image: " << normalized_path << std::endl;
        return false;
    }

    // Extract just the filename for the output file
    size_t pos = normalized_path.find_last_of('/');
    std::string img_name = (pos != std::string::npos) ? normalized_path.substr(pos + 1) : normalized_path;

    std::cout << "Image loaded successfully. Size: " << img.cols << "x" << img.rows << std::endl;

    // Process image
    cv::Mat res = DarkChannel::dehaze(img);
    std::cout << "Dehazing completed. Result size: " << res.rows << "x" << res.cols << std::endl;

    // Save in the project directory
    std::string output_path = project_path + "dehazed_" + img_name;
    cv::imwrite(output_path, res);
    std::cout << "Result saved as: " << output_path << std::endl;

    // Create named windows with the WINDOW_NORMAL flag to allow resizing
    cv::namedWindow("Original", cv::WINDOW_NORMAL);
    cv::namedWindow("Dehazed Result", cv::WINDOW_NORMAL);

    // Position the windows side by side
    cv::moveWindow("Original", 50, 50);  // Position original image window
    cv::moveWindow("Dehazed Result", 50 + img.cols + 20, 50);  // Position result window to the right

    // Display the result
    cv::imshow("Original", img);
    cv::imshow("Dehazed Result", res);
    cv::waitKey(1000); // wait indefinitely until a key is pressed

    return true;
}

int main(int argc, char** argv) {
    try {
        std::string project_path = "C:/Users/esther/source/repos/Dehaze/";

        // Check if we should use interactive mode
        bool interactive_mode = true;
        std::string img_path;

        if (argc > 1) {
            // If arguments provided, process the specified image
            interactive_mode = false;
            std::string arg_path = argv[1];

            // Check if the argument is a relative path
            if (arg_path.find(':') == std::string::npos) {
                // It's a relative path, combine with project path
                img_path = project_path + arg_path;
            }
            else {
                // It's an absolute path, use it directly
                img_path = arg_path;
            }

            processImage(img_path, project_path);
        }
        else {
            // Enter interactive mode
            int choice = -1;
            while (choice != 0) {
                std::cout << "=== Dehaze Interactive Mode ===" << std::endl;
                std::cout << "Options:" << std::endl;
                std::cout << "  1: Enter image path manually" << std::endl;
                std::cout << "  2: Use file dialog to select image" << std::endl;
                std::cout << "  3: Process multiple images" << std::endl;
                std::cout << "  0: Exit" << std::endl;
                
                std::cout << "\nEnter your choice (0-3): ";
                std::cin >> choice;
                std::cin.ignore(); // Clear the newline

            
                switch (choice) {
                case 0:
                    std::cout << "Exiting program." << std::endl;
                    break;

                case 1: {
                    // Manual path entry
                    std::cout << "Enter image path (or 'exit' to return to menu): ";
                    std::getline(std::cin, img_path);
                    if (img_path == "exit" || img_path == "quit") {
                        break;
                    }
                    processImage(img_path, project_path);
                    break;
                }

                case 2: {
                    // File dialog
                    img_path = getImageFile();
                    if (!img_path.empty()) {
                        processImage(img_path, project_path);
                    }
                    else {
                        std::cout << "No file selected." << std::endl;
                    }
                    break;
                }

                case 3: {
                    // Process multiple images
                    std::cout << "Enter 'exit' at any time to return to menu." << std::endl;
                    while (true) {
                        std::cout << "\nSelect option for next image:" << std::endl;
                        std::cout << "  1: Enter path manually" << std::endl;
                        std::cout << "  2: Use file dialog" << std::endl;
                        std::cout << "  0: Return to main menu" << std::endl;

                        int subChoice;
                        std::cout << "Choice: ";
                        std::cin >> subChoice;
                        std::cin.ignore(); // Clear the newline

                        if (subChoice == 0) {
                            break;
                        }
                        else if (subChoice == 1) {
                            std::cout << "Enter image path: ";
                            std::getline(std::cin, img_path);
                            if (img_path == "exit" || img_path == "quit") {
                                break;
                            }
                        }
                        else if (subChoice == 2) {
                            img_path = getImageFile();
                            if (img_path.empty()) {
                                std::cout << "No file selected." << std::endl;
                                continue;
                            }
                        }
                        else {
                            std::cout << "Invalid choice." << std::endl;
                            continue;
                        }

                        processImage(img_path, project_path);
                    }
                    break;
                }

                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
        }

        cv::destroyAllWindows();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
}