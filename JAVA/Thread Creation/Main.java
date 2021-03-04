package com.assignment1ex;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class Main {

    public static void main(String[] args) throws InterruptedException, IOException {
        FileWriter writer = new FileWriter("thread_creation_java.csv", false);
        BufferedWriter bufferedWriter = new BufferedWriter(writer);

        for ( int i = 0; i < 100; i++){
            double threadCreationElapsedTime = 0.0;
            for (int j = 0; j < 1000; j++) {
                double start = System.currentTimeMillis();
                ThreadFunction function = new ThreadFunction();
                Thread thread1 = new Thread(function);
                thread1.start();
                double end = System.currentTimeMillis();
                threadCreationElapsedTime += (end - start);
            }
            System.out.println(threadCreationElapsedTime/1000);
            try {
                //bufferedWriter.write(String.valueOf(i));
                //bufferedWriter.write(",");
                bufferedWriter.write(String.valueOf(threadCreationElapsedTime/1000));
                bufferedWriter.newLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            System.out.println();
        }
        bufferedWriter.close();

    }
}
