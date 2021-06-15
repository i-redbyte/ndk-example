package com.github.iredbyte.ndk_example

import android.os.Bundle
import android.view.View
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    init {
        System.loadLibrary("hellojni")
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val tvHello = findViewById<TextView>(R.id.text_view_hello_neon)
        tvHello.text = stringFromJNI()
    }

    external fun stringFromJNI(): String?

}