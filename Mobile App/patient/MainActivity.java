package com.example.youssef.test2;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextUtils;
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
import com.google.firebase.database.Query;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";
    public static final int RC_SIGN_IN = 1;



    private TextView mUsername;
    private TextView mRFID;
    private TextView mAge;
    private TextView tempText;
    private TextView pulseText;
    private TextView oxygenText;
    private Button editProfile;

    private EditText AgeEditText;
    private EditText nameEditText;
    private Button submitButton;
    private TextView hideText;

    private FirebaseAuth mFirebaseAuth;
    private FirebaseAuth.AuthStateListener mAuthStateListener;

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
        mDatabaseReference=FirebaseDatabase.getInstance().getReference();
        mUsername=(TextView) findViewById(R.id.username_textView);
        mRFID=(TextView) findViewById(R.id.rfid_textView);
        mAge=(TextView) findViewById(R.id.age_textView);
        tempText =(TextView) findViewById(R.id.temp_textView);
        pulseText =(TextView) findViewById(R.id.pulse_textView);
        oxygenText =(TextView) findViewById(R.id.oxygen_textView);
        editProfile=(Button) findViewById(R.id.edit_profile_button);

        AgeEditText =(EditText) findViewById(R.id.age_editText);
        nameEditText=(EditText) findViewById(R.id.name_editText);
        submitButton=(Button) findViewById(R.id.submit_button);
        hideText= (TextView) findViewById(R.id.hide_textView);

       submitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(TextUtils.isEmpty(nameEditText.getText().toString())|TextUtils.isEmpty(AgeEditText.getText().toString())){
                    Toast.makeText(getApplicationContext(), "There is blank spaces", Toast.LENGTH_SHORT).show();
                }
                else{String S=FirebaseAuth.getInstance().getCurrentUser().getUid();
                User user = new User( nameEditText.getText().toString() ,AgeEditText.getText().toString() ,S);
                Reading readingg=new Reading("","","");
                mMessagesDatabaseReference.child(mFirebaseAuth.getCurrentUser().getUid()).push().setValue(user);
                mDatabaseReference.child(FirebaseAuth.getInstance().getCurrentUser().getDisplayName()).push().setValue(readingg);
                mDatabaseReference.child("userData").child(FirebaseAuth.getInstance().getCurrentUser().getDisplayName()).push().setValue(user);



                AgeEditText.setVisibility(View.GONE);
                submitButton.setVisibility(View.GONE);
                nameEditText.setVisibility(View.GONE);
                hideText.setVisibility(View.GONE);
                AgeEditText.setText("");
                nameEditText.setText("");
                AgeEditText.setHint("Age");
                nameEditText.setHint("Name");}
                //mUsername.setText(uid);


            }
        });
        editProfile.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {

                nameEditText.setVisibility(View.VISIBLE);
                AgeEditText.setVisibility(View.VISIBLE);
                submitButton.setVisibility(View.VISIBLE);
                hideText.setVisibility(View.VISIBLE);


            }
        });
        hideText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AgeEditText.setVisibility(View.GONE);
                submitButton.setVisibility(View.GONE);
                nameEditText.setVisibility(View.GONE);
                hideText.setVisibility(View.GONE);
                AgeEditText.setText("");
                nameEditText.setText("");
                AgeEditText.setHint("Age");
                nameEditText.setHint("Name");

            }
        });



        querygetRFID();

      //  attachDatabaseReadListener();




        mFirebaseAuth = FirebaseAuth.getInstance();
        mAuthStateListener = new FirebaseAuth.AuthStateListener() {
            @Override
            public void onAuthStateChanged(@NonNull FirebaseAuth firebaseAuth) {
                FirebaseUser user = firebaseAuth.getCurrentUser();

                if (user != null) {
                    // User is signed in
                    onSignedInInitialize(user.getDisplayName());
                   mRFID.setText(user.getDisplayName());
                } else {
                    // User is signed out
                    onSignedOutCleanup();
                    startActivityForResult(
                            AuthUI.getInstance()
                                    .createSignInIntentBuilder()
                                    .setIsSmartLockEnabled(false)
                                    .setProviders(
                                            AuthUI.EMAIL_PROVIDER)
                                    .build(),
                            RC_SIGN_IN);
                }
            }
        };


    }
    private void querygetRFID(){
       DatabaseReference reference= FirebaseDatabase.getInstance().getReference().child(FirebaseAuth.getInstance().getCurrentUser().getUid());
        final Query query =reference.orderByChild("uid").equalTo(FirebaseAuth.getInstance().getCurrentUser().getUid());
        final String St;
        query.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                if(dataSnapshot.exists()){
                    for (DataSnapshot snapshot :dataSnapshot.getChildren()){
                        User use =snapshot.getValue(User.class);

                        mUsername.setText(use.getName());
                        mAge.setText(use.getAge());



                    }
                }
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });

    }
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == RC_SIGN_IN) {
            if (resultCode == RESULT_OK) {
                // Sign-in succeeded, set up the UI
                Toast.makeText(this, "Signed in!", Toast.LENGTH_SHORT).show();
            } else if (resultCode == RESULT_CANCELED) {
                // Sign in was canceled by the user, finish the activity
                Toast.makeText(this, "Sign in canceled", Toast.LENGTH_SHORT).show();
                finish();
            }
        }
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
        querygetRFID();
        attachDatabaseReadListener();

    }

    public void onSignedOutCleanup() {

        detachDatabaseReadListener();
        mUsername.setText("");
        mAge.setText("");
        mRFID.setText("");
        tempText.setText("");
        oxygenText.setText("");
        pulseText.setText("");
        AgeEditText.setText("");
        nameEditText.setText("");
        AgeEditText.setHint("Age");
        nameEditText.setHint("Name");
    }

    public void attachDatabaseReadListener() {
        if (mChildEventListener == null) {
            String T=FirebaseAuth.getInstance().getCurrentUser().getDisplayName();
          mChildEventListener = new ChildEventListener() {
            @Override
            public void onChildAdded(DataSnapshot dataSnapshot, String s) {

                if (dataSnapshot.exists()) {
                    Reading readings = dataSnapshot.getValue(Reading.class);
                    tempText.setText(readings.getReadingTemp().toString().trim());
                    pulseText.setText(readings.getReadingPulse().toString().trim());
                    oxygenText.setText(readings.getReadingOxygen().toString().trim());
                }
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

            mMessagesDatabaseReference.child(T).addChildEventListener(mChildEventListener);

        }

    }


    public void detachDatabaseReadListener() {

        if (mChildEventListener != null) {
            mMessagesDatabaseReference.removeEventListener(mChildEventListener);
            mChildEventListener = null;
        }

    }
}
