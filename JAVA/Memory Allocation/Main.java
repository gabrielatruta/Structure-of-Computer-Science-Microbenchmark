package com.assignment1ex;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException {
        FileWriter writer = new FileWriter("dynamic_allocation_java.csv", false);
        BufferedWriter bufferedWriter = new BufferedWriter(writer);
        for (int i = 0; i < 1000; i++) {
            double dynamicElapsedTime = 0.0;
            for (int j = 0; j < 100000; j++) {
                double start = System.currentTimeMillis();
                int[] array = new int[333];
                double stop = System.currentTimeMillis();
                dynamicElapsedTime += (stop - start);
            }
            System.out.println(dynamicElapsedTime/100000);
            try {
                //bufferedWriter.write(String.valueOf(i));
                //bufferedWriter.write(",");
                bufferedWriter.write(String.valueOf(dynamicElapsedTime/100000));
                bufferedWriter.newLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        bufferedWriter.close();


    }
}
