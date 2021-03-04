package com.assignment1ex;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

public class Main {

    public static void main(String[] args) throws IOException {
        FileWriter writer = new FileWriter("dynamic_memory_access_java.csv", false);
        BufferedWriter bufferedWriter = new BufferedWriter(writer);
        for (int i = 0; i < 1000; i++) {
            double dynamicElapsedTime = 0.0;
            double start;
            double stop;
            int[] array1 = new int[333];
            for (int j = 0; j < 333; j++)
                array1[j] = j++;
            for (int j = 0; j < 100000; j++ ) {
                int[] array2 = new int[333];
                start = System.currentTimeMillis();
                array2 = Arrays.copyOf(array1, 333);
                stop = System.currentTimeMillis();
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
