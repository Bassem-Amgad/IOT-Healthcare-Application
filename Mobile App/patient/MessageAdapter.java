package com.example.youssef.test2;

/**
 * Created by Youssef on 6/15/2018.
 */
import android.app.Activity;
import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;


import java.util.List;

public class MessageAdapter extends ArrayAdapter<User> {
    public MessageAdapter(Context context, int resource, List<User> objects) {
        super(context, resource, objects);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        if (convertView == null) {
            convertView = ((Activity) getContext()).getLayoutInflater().inflate(R.layout.item_message, parent, false);
        }


        TextView nameTextView = (TextView) convertView.findViewById(R.id.nameTextView);

        TextView RFIDTextView = (TextView) convertView.findViewById(R.id.RFIDTextView);
        TextView ageTextView = (TextView) convertView.findViewById(R.id.ageTextView);


        User user = getItem(position);




        //nameTextView.setText(user.getName());
        //RFIDTextView.setText(user.getRFID());
        //ageTextView.setText(user.getAge());

        return convertView;
    }
}
