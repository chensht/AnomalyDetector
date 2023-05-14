cmake_minimum_required(VERSION 3.20)
project(ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex2 anomaly_detection_util.cpp anomaly_detection_util.h training.cpp timeseries.cpp timeseries.h AnomalyDetector.h SimpleAnomalyDetector.h MainTrain.cpp SimpleAnomalyDetector.cpp minCircle.h minCircle.cpp HybridAnomalyDetector.h HybridAnomalyDetector.cpp CLI.h commands.h CLI.cpp input.txt output.txt expectedOutput.txt Server.cpp Server.h)
