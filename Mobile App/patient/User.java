package com.example.youssef.test2;

/**
 * Created by Youssef on 6/15/2018.
 */

public class User {



    private String age;
    private String name;
private String uid;


    public User() {
    }

    public User(String name,String age,String uid) {


        this.name=name;
        this.age=age;
        this.uid=uid;


    }

    public String getAge() {
        return age;
    }

    public void setAge(String age) {
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getUid() {
        return uid;
    }

    public void setUid(String uid) {
        this.uid = uid;
    }
}
