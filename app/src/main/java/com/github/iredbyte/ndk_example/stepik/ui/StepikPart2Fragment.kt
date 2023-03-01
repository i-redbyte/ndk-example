package com.github.iredbyte.ndk_example.stepik.ui

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.github.iredbyte.ndk_example.R

class StepikPart2Fragment : Fragment() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? = inflater.inflate(R.layout.fragment_stepik_part2, container, false)

//    companion object {
//        @JvmStatic
//        fun newInstance() = StepikPart2Fragment()
//    }
}