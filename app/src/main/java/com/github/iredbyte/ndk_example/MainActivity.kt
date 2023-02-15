package com.github.iredbyte.ndk_example

import android.os.Bundle
import android.util.Log
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.github.iredbyte.ndk_example.storage.Stepik

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val tvHello = findViewById<TextView>(R.id.text_view_hello_neon)
        val stepik = Stepik()
        stepik.helloWord()
//        tvHello.text = pos.stringFromJNI()
//        pos.markovPoissonProcess()?.let {
//            Log.d("_debug", "Markov:${it.size} ");
//            it.forEachIndexed { index, arr -> Log.d("_debug", "[$index] : $arr "); }
//        }
    }

}