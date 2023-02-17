package com.github.iredbyte.ndk_example

import android.annotation.SuppressLint
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
        val part1 = findViewById<TextView>(R.id.stepik_power_solution)
        part1.setOnClickListener { stepik.helloWord() }
        @SuppressLint("SetTextI18n")
        fun power() {
            val powerCpp: (Int, Int) -> String = { x, y ->
                val power = stepik.power(x, y)
                val powerRecurs = stepik.power(x, y)
                "$x^$y with power = $power; recursion power = $powerRecurs"
            }
            part1.text = powerCpp(2, 8)
            val x = (0..100).random()
            val y = (0..100).random()
            val z = (0..100).random()
            val oldText = part1.text
            part1.text = "$oldText\nMaximum of three numbers ($x; $y; $z;) = ${stepik.max3(x, y, z)}" +
                    "\nLog2(1024) = ${stepik.log2(1024)}"
        }
        power()
    }

}