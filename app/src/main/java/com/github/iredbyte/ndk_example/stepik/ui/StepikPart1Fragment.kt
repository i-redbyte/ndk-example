package com.github.iredbyte.ndk_example.stepik.ui

import android.annotation.SuppressLint
import android.content.Context
import android.os.Bundle
import android.view.View
import android.view.inputmethod.InputMethodManager
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.widget.AppCompatButton
import androidx.fragment.app.Fragment
import com.github.iredbyte.ndk_example.R
import com.github.iredbyte.ndk_example.stepik.storage.Stepik
import com.google.android.material.snackbar.Snackbar

class StepikPart1Fragment : Fragment(R.layout.fragment_stepik_part1) {
    private val stepik = Stepik()
    private val btnSolveQuadraticEquation by lazy { requireView().findViewById<AppCompatButton>(R.id.btnSolveQuadraticEquation) }
    private val etValueA by lazy { requireView().findViewById<EditText>(R.id.etValueA) }
    private val etValueB by lazy { requireView().findViewById<EditText>(R.id.etValueB) }
    private val etValueC by lazy { requireView().findViewById<EditText>(R.id.etValueC) }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        solutionStepikPart()
    }

    private fun solutionStepikPart() {
        val part1 = requireView().findViewById<TextView>(R.id.stepik_power_solution)
        part1.setOnClickListener { stepik.helloWord() }
        btnSolveQuadraticEquation.setOnClickListener {
            quadraticEquation(it)
        }
        @SuppressLint("SetTextI18n")
        fun power() {
            val powerCpp: (Int, Int) -> String = { x, y ->
                val power = stepik.power(x, y)
                val powerRecurs = stepik.powerRecursion(x, y)
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
        val imm: InputMethodManager =
            requireActivity().getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
        imm.hideSoftInputFromWindow(view.windowToken, 0)
        try {
            val a = etValueA.text.toString().toInt()
            val b = etValueB.text.toString().toInt()
            val c = etValueC.text.toString().toInt()
            Snackbar.make(
                requireView(),
                stepik.quadraticEquation(a, b, c),
                Snackbar.LENGTH_LONG
            )
                .show()
        } catch (error: NumberFormatException) {
            Toast.makeText(requireContext(), getString(R.string.stepik_error_quadratic), Toast.LENGTH_LONG).show()
        }
    }
}