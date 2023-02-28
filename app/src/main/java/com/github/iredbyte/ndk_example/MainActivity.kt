package com.github.iredbyte.ndk_example

import android.annotation.SuppressLint
import android.content.Context
import android.os.Bundle
import android.util.Log
import android.view.View
import android.view.inputmethod.InputMethodManager
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.AppCompatButton
import com.github.iredbyte.ndk_example.storage.Stepik
import com.google.android.material.snackbar.Snackbar

class MainActivity : AppCompatActivity() {
    private val stepik = Stepik()
    private val btnSolveQuadraticEquation by lazy { findViewById<AppCompatButton>(R.id.btnSolveQuadraticEquation) }
    private val etValueA by lazy { findViewById<EditText>(R.id.etValueA) }
    private val etValueB by lazy { findViewById<EditText>(R.id.etValueB) }
    private val etValueC by lazy { findViewById<EditText>(R.id.etValueC) }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        solutionStepikPart1()
        solutionStepikPart2()
    }

    private fun solutionStepikPart2() {
        val arr = intArrayOf(1, 2, 3, 4, 5)
        val transform = {element: Int -> "$element "}
        Log.d("_debug", "solutionStepikPart2: ${arr.map(transform)}")
        stepik.rotate(arr, arr.size, 2)
        Log.d("_debug", "solutionStepikPart2: ${arr.map(transform)}")
    }

    private fun solutionStepikPart1() {
        val part1 = findViewById<TextView>(R.id.stepik_power_solution)
        part1.setOnClickListener { stepik.helloWord() }
        btnSolveQuadraticEquation.setOnClickListener {
            quadraticEquation(it)
        }
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

    private fun quadraticEquation(view: View) {
        val imm: InputMethodManager = getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
        imm.hideSoftInputFromWindow(view.windowToken, 0)
        try {
            val a = etValueA.text.toString().toInt()
            val b = etValueB.text.toString().toInt()
            val c = etValueC.text.toString().toInt()
            Snackbar.make(
                view,
                stepik.quadratic_equation(a, b, c),
                Snackbar.LENGTH_LONG
            )
                .show()
        } catch (error: NumberFormatException) {
            Toast.makeText(this, getString(R.string.error), Toast.LENGTH_LONG).show()
        }
    }

}