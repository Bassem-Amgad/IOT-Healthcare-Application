package com.example.youssef.test2;

/**
 * Created by Youssef on 6/15/2018.
 */

public class User {



    private String RFID;



    public User() {
    }

    public User(String RFID) {


        this.RFID=RFID;


    }





    public String getRFID() {
        return RFID;
    }

    public void setRFID(String RFID) {
        this.RFID = RFID;
    }
}