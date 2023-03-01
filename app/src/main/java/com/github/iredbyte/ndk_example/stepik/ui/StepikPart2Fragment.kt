package com.github.iredbyte.ndk_example.stepik.ui

import android.os.Bundle
import android.view.View
import android.widget.TextView
import androidx.appcompat.widget.AppCompatButton
import androidx.fragment.app.Fragment
import com.github.iredbyte.ndk_example.R
import com.github.iredbyte.ndk_example.stepik.storage.Stepik

class StepikPart2Fragment : Fragment(R.layout.fragment_stepik_part2) {
    private val stepik = Stepik()
    private val btnRotate by lazy { requireView().findViewById<AppCompatButton>(R.id.btnRotate) }
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        setupViews()
        solutionStepikPart2()
    }

    private fun setupViews() {
        btnRotate.setOnClickListener { rotateArray(getRandomArray()) }
    }

    private fun solutionStepikPart2() {
        rotateArray(getRandomArray())
        concatStrings()
    }

    private fun concatStrings() {
        val s = "I love "
        val result = "result strcat fun: ${stepik.strcat(s, "C++")}"
        requireView().findViewById<TextView>(R.id.tvConcatString).text = result
    }

    private fun getRandomArray(maxN: Int = 10): IntArray {
        val n = (3..10).random()
        val array = IntArray(n)
        repeat((0 until n).count()) { i -> array[i] = (0..100).random() }
        return array
    }

    private fun rotateArray(array: IntArray, shift: Int = 2) {
        val transform = { element: Int -> "$element " }
        val start = "Array before: ${array.map(transform)}"
        val result = requireView().findViewById<TextView>(R.id.tvRotateArray)
        stepik.rotate(array, array.size, shift)
        val resultText = "$start\nArray after: ${array.map(transform)}"
        result.text = resultText
    }

}