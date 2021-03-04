import csv

import matplotlib.pyplot as plt
import numpy as np
import platform,socket,re,uuid,json,psutil,logging
import multiprocessing
#import numpy as np
import PySimpleGUI as main_window
import PySimpleGUI as new_window

x_axis = [i for i in range(1, 1001, 1)]

#Memory allocation
C_static_memory_allocation = 0.0
CPP_static_memory_allocation = 0.0

C_dynamic_memory_allocation = 0.0
CPP_dynamic_memory_allocation = 0.0
JAVA_dynamic_memory_allocation = 0.0

#Memory_access
C_static_memory_access = 0.0
CPP_static_memory_access = 0.0

C_dynamic_memory_access = 0.0
CPP_dynamic_memory_access = 0.0
JAVA_dynamic_memory_access = 0.0

#Thread creation
C_thread_creation = 0.0
CPP_thread_creation = 0.0
JAVA_thread_creation = 0.0

def read_csv_file_memory (file_name):
    sum = 0
    with open(file_name, newline='') as csv_file:
        rows = list(csv.reader(csv_file))

    for row in rows:
        sum += float(row[0])

    average.append(float(sum / 1000))
    print(f'average {average}')

def read_csv_file_thread (file_name):
    sum = 0
    with open(file_name, newline='') as csv_file:
       rows = list(csv.reader(csv_file))

    for row in rows:
        sum += float(row[0])

    average.append(float(sum / 100))
    print(f'average {average}')

main_window.theme('Kayak')
new_window.theme('Kayak')
layout_main = [[main_window.Text("Microbenchmark for multiple operations")],
          [main_window.Text("by Truta Gabriela")],
          [main_window.Text("SCS project 2021")],
          [main_window.Button("Memory allocation")],
          [main_window.Button("Memory access")],
          [main_window.Button("Thread creation")],
          [main_window.Button("Close")]]
window = main_window.Window(title="Microbenchmark", size=(300, 300), layout = layout_main)

while True:
    event, values = window.read()
    if event == main_window.WIN_CLOSED or event == "Close":
        break


    if event == "Memory allocation":
        newButtons2 = [[new_window.Button("Static memory allocation")], [new_window.Button("Dynamic memory allocation")], [new_window.Button("Close")]]
        win1 = new_window.Window(title="Memory Allocation", size=(300, 300), layout=newButtons2)

        while True:
            ev, val = win1.read()
            if ev == new_window.WIN_CLOSED or ev == "Close":
                win1.close()
                break
            if ev == "Dynamic memory allocation":
                average = []
                read_csv_file_thread("dynamic_memory_allocation_c.csv")
                C_dynamic_memory_allocation = average[0]

                average = []
                read_csv_file_thread("dynamic_memory_allocation_c_plus.csv")
                CPP_dynamic_memory_allocation = average[0]

                average = []
                read_csv_file_thread("dynamic_allocation_java.csv")
                JAVA_dynamic_memory_allocation = average[0]
                print(
                    f'values{C_dynamic_memory_allocation, CPP_dynamic_memory_allocation, JAVA_dynamic_memory_allocation}')

                names = ["C", "C++", "Java"]
                values = [C_dynamic_memory_allocation, CPP_dynamic_memory_allocation, JAVA_dynamic_memory_allocation]
                y_pos = np.arange(len(names))
                plt.bar(y_pos, values, align='center', alpha=0.5)
                plt.xticks(y_pos, names)
                plt.ylabel('Elapsed time in miliseconds')
                plt.title('Dynamic memory allocation')
                plt.show()


            if ev == "Static memory allocation":
                average = []
                read_csv_file_memory("static_memory_allocation_c.csv")
                C_static_memory_allocation = average[0]

                average = []
                read_csv_file_thread("static_memory_allocation_c_plus.csv")
                CPP_static_memory_allocation = average[0]
                print(f'values{CPP_static_memory_allocation, C_static_memory_allocation}')

                names = ["C", "C++"]
                values = [C_static_memory_allocation*10, CPP_static_memory_allocation]
                y_pos = np.arange(len(names))
                plt.bar(y_pos, values, align='center', alpha=0.5)
                plt.xticks(y_pos, names)
                plt.ylabel('Elapsed time in miliseconds')
                plt.title('Static memory allocation comparison')
                plt.show()



    if event == "Thread creation":
        average = []
        read_csv_file_thread("thread_creation_c_plus.csv")
        C_thread_creation = average[0]

        average = []
        read_csv_file_thread("thread_creation_c.csv")
        CPP_thread_creation = average[0]

        average = []
        read_csv_file_thread("thread_creation_java.csv")
        print(f'values{C_thread_creation, CPP_thread_creation, JAVA_thread_creation}')
        JAVA_thread_creation = average[0]

        names = ["C", "C++", "Java"]
        values = [C_thread_creation, CPP_thread_creation, JAVA_thread_creation]
        y_pos = np.arange(len(names))
        plt.bar(y_pos, values, align='center', alpha=0.5)
        plt.xticks(y_pos, names)
        plt.ylabel('Elapsed time in miliseconds')
        plt.title('Thread Creation Comparison')
        plt.show()

    if event == "Memory access":
        newButtons2 = [[new_window.Button("Static memory access")],
                       [new_window.Button("Dynamic memory access")], [new_window.Button("Close")]]
        win1 = new_window.Window(title="Memory Access", size=(300, 300), layout=newButtons2)

        while True:
            ev, val = win1.read()
            if ev == new_window.WIN_CLOSED or ev == "Close":
                win1.close()
                break

            if ev == "Static memory access":
                average = []
                read_csv_file_memory("static_memory_access_c.csv")
                C_static_memory_access = average[0]

                average = []
                read_csv_file_thread("static_memory_access_c_plus.csv")
                CPP_static_memory_access = average[0]
                print(f'values{C_static_memory_access, CPP_static_memory_access}')

                names = ["C", "C++"]
                values = [C_static_memory_access*10, CPP_static_memory_access]
                y_pos = np.arange(len(names))
                plt.bar(y_pos, values, align='center', alpha=0.5)
                plt.xticks(y_pos, names)
                plt.ylabel('Elapsed time in miliseconds')
                plt.title('Static memory access comparison')
                plt.show()

            if ev == "Dynamic memory access":
                average = []
                read_csv_file_thread("dynamic_memory_access_c.csv")
                C_dynamic_memory_access = average[0]

                average = []
                read_csv_file_thread("dynamic_memory_access_c_plus.csv")
                CPP_dynamic_memory_access = average[0]

                average = []
                read_csv_file_thread("dynamic_memory_access_java.csv")
                JAVA_dynamic_memory_access = average[0]
                print(
                    f'values{C_dynamic_memory_access, CPP_dynamic_memory_access, JAVA_dynamic_memory_access}')

                names = ["C", "C++", "Java"]
                values = [C_dynamic_memory_access, CPP_dynamic_memory_access, JAVA_dynamic_memory_access]
                y_pos = np.arange(len(names))
                plt.bar(y_pos, values, align='center', alpha=0.5)
                plt.xticks(y_pos, names)
                plt.ylabel('Elapsed time in miliseconds')
                plt.title('Dynamic memory access')
                plt.show()

window.close()





