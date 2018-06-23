package com.example.youssef.project;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class DoctorActivity extends AppCompatActivity {
    EditText editText,doctorpassEditText;
    Button logIn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
       setContentView(R.layout.activity_doctor);

        editText =(EditText) findViewById(R.id.name_edit_text);
        doctorpassEditText =(EditText) findViewById(R.id.doctor_pass_edit_text);
             logIn = (Button) findViewById(R.id.log_in_button);
            logIn.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {

                    String nameEditText = editText.getText().toString();
                    String passEditText = doctorpassEditText.getText().toString();
                    if(nameEditText.equals("Youssef") && passEditText.equals("1234") ){
                        Intent doctor2Intent = new Intent(DoctorActivity.this, Doctor2Activity.class);
                        startActivity(doctor2Intent);}
                        else{
                        Toast.makeText(DoctorActivity.this,"Incorrect Id Or Password",Toast.LENGTH_SHORT).show();
                    }


                }
            });


    }

}
