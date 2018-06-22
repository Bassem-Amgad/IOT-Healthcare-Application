package com.example.youssef.test2;

/**
 * Created by Youssef on 6/15/2018.
 */

public class Reading {




    private String readingOxygen;
    private String readingPulse;
    private String readingTemp;


    public Reading() {
    }

    public Reading(String readingOxygen,String readingPulse,String readingTemp) {
        this.readingTemp = readingTemp;
        this.readingPulse = readingPulse;
        this.readingOxygen = readingOxygen;


    }

    public String getReadingTemp() {
        return readingTemp;
    }

    public void setReadingTemp(String readingTemp) {
        this.readingTemp = readingTemp;
    }

    public String getReadingPulse() {
        return readingPulse;
    }

    public void setReadingPulse(String readingPulse) {
        this.readingPulse = readingPulse;
    }

    public String getReadingOxygen() {
        return readingOxygen;
    }

    public void setReadingOxygen(String readingOxygen) {
        this.readingOxygen = readingOxygen;
    }
}