package com.github.iredbyte.ndk_example

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.github.iredbyte.ndk_example.storage.Stepik

class MainActivity : AppCompatActivity() {
    private val stepik = Stepik()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        solutionStepikPart1()
    }

    private fun solutionStepikPart1() {
        val tvHello = findViewById<TextView>(R.id.stepik_power_solution)
        stepik.helloWord()
        fun power() {
            val powerCpp: (Int, Int) -> String = { x, y ->
                val power = stepik.power(x, y)
                val powerRecurs = stepik.power(x, y)
                "$x^$y with power = $power; recursion power = $powerRecurs"
            }
            tvHello.text = powerCpp(2, 8)
        }
        power()
    }

}