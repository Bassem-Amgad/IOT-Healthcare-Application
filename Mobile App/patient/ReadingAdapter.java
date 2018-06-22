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

public class ReadingAdapter extends ArrayAdapter<Reading> {
    public ReadingAdapter(Context context, int resource, List<Reading> objects) {
        super(context, resource, objects);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        if (convertView == null) {
            convertView = ((Activity) getContext()).getLayoutInflater().inflate(R.layout.item_reading, parent, false);
        }


        TextView readingTextView = (TextView) convertView.findViewById(R.id.ReadingTextView);



        Reading reading = getItem(position);




        readingTextView.setText(reading.getReadingTemp());


        return convertView;
    }
}
