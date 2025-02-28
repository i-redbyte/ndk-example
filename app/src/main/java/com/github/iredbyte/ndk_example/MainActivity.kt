package com.github.iredbyte.ndk_example

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.AppCompatButton
import com.github.iredbyte.ndk_example.ndkman.keyvalue.NdkManActivity
import com.github.iredbyte.ndk_example.stepik.ui.StepikActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        setupViews()
    }

    private fun setupViews() {
        findViewById<AppCompatButton>(R.id.btnStepik).setOnClickListener {
            startActivity(StepikActivity.newInstance(this))
        }
        findViewById<AppCompatButton>(R.id.btnNdkMan).setOnClickListener {
            startActivity(NdkManActivity.newInstance(this))
        }
    }

}