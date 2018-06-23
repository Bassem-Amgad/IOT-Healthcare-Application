package com.example.youssef.project;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView doctors = (TextView) findViewById(R.id.Doctors);
        doctors.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent doctorIntent = new Intent(MainActivity.this,DoctorActivity.class);
                startActivity(doctorIntent);
            }
        });


        TextView patients = (TextView) findViewById(R.id.Patients);
        patients.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent patientIntent = new Intent(MainActivity.this, PatientActivity.class);
                startActivity(patientIntent);
            }
        });
    }


}
