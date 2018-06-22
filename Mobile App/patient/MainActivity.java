package com.example.youssef.test2;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextWatcher;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;


import com.firebase.ui.auth.AuthUI;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";
    public static final int RC_SIGN_IN = 1;



    private TextView mUsername;
    private TextView tempText;
    private TextView pulseText;
    private TextView oxygenText;
    private Button editProfile;

    private EditText RFIDEditText;
    private Button submitButton;

    private FirebaseAuth mFirebaseAuth;
    private FirebaseAuth.AuthStateListener mAuthStateListener;

    public String Naming;

    // Firebase instance variables
    private FirebaseDatabase mFirebaseDatabase;
    private DatabaseReference mMessagesDatabaseReference;
    private DatabaseReference mDatabaseReference;
    private ChildEventListener mChildEventListener;
    private ChildEventListener mChildEventListener1;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        // Initialize Firebase components
        mFirebaseDatabase = FirebaseDatabase.getInstance();

        mMessagesDatabaseReference = mFirebaseDatabase.getReference();

        mUsername=(TextView) findViewById(R.id.username_textView);
        tempText =(TextView) findViewById(R.id.temp_textView);
        pulseText =(TextView) findViewById(R.id.pulse_textView);
        oxygenText =(TextView) findViewById(R.id.oxygen_textView);
        editProfile=(Button) findViewById(R.id.edit_profile_button);

        RFIDEditText =(EditText) findViewById(R.id.rfid_editText);
        submitButton=(Button) findViewById(R.id.submit_button);

       submitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                User user = new User( RFIDEditText.getText().toString()  );
                mMessagesDatabaseReference.child(mFirebaseAuth.getCurrentUser().getUid()).push().setValue(user);


                RFIDEditText.setVisibility(View.GONE);
                submitButton.setVisibility(View.GONE);
                //mUsername.setText(uid);


            }
        });
        editProfile.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {

                RFIDEditText.setVisibility(View.VISIBLE);
                submitButton.setVisibility(View.VISIBLE);


            }
        });





        mFirebaseAuth = FirebaseAuth.getInstance();
        mAuthStateListener = new FirebaseAuth.AuthStateListener() {
            @Override
            public void onAuthStateChanged(@NonNull FirebaseAuth firebaseAuth) {
                FirebaseUser user = firebaseAuth.getCurrentUser();

                if (user != null) {
                    // User is signed in
                    onSignedInInitialize(user.getDisplayName());
                    mUsername.setText(user.getDisplayName());
                } else {
                    // User is signed out
                    onSignedOutCleanup();
                    startActivityForResult(
                            AuthUI.getInstance()
                                    .createSignInIntentBuilder()
                                    .setIsSmartLockEnabled(false)
                                    .setProviders(
                                            AuthUI.EMAIL_PROVIDER,
                                            AuthUI.GOOGLE_PROVIDER)
                                    .build(),
                            RC_SIGN_IN);
                }
            }
        };


    }

    @Override
    protected void onResume() {
        super.onResume();
        mFirebaseAuth.addAuthStateListener(mAuthStateListener);
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (mAuthStateListener != null) {
            mFirebaseAuth.removeAuthStateListener(mAuthStateListener);

        }

        detachDatabaseReadListener();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.main_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.sign_out_menu:
                AuthUI.getInstance().signOut(this);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    public void onSignedInInitialize(String username) {

        attachDatabaseReadListener();
    }

    public void onSignedOutCleanup() {

        detachDatabaseReadListener();
    }

    public void attachDatabaseReadListener() {
        if (mChildEventListener == null) {
          mChildEventListener = new ChildEventListener() {
            @Override
            public void onChildAdded(DataSnapshot dataSnapshot, String s) {

                Reading readings = dataSnapshot.getValue(Reading.class);
                tempText.setText(readings.getReadingTemp());
                pulseText.setText(readings.getReadingPulse());
                oxygenText.setText(readings.getReadingOxygen());
            }

            public void onChildChanged(DataSnapshot dataSnapshot, String s) {
            }

            public void onChildRemoved(DataSnapshot dataSnapshot) {
            }

            public void onChildMoved(DataSnapshot dataSnapshot, String s) {
            }

            public void onCancelled(DatabaseError databaseError) {
            }
        };

            mMessagesDatabaseReference.child("C95ADE39").child("readings").addChildEventListener(mChildEventListener);

        }

    }


    public void detachDatabaseReadListener() {

        if (mChildEventListener != null) {
            mMessagesDatabaseReference.removeEventListener(mChildEventListener);
            mChildEventListener = null;
        }

    }
}