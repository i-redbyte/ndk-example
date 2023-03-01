package com.github.iredbyte.ndk_example.stepik.ui

import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentActivity
import androidx.viewpager2.adapter.FragmentStateAdapter

class StepikPageAdapter (
    fragmentActivity: FragmentActivity
) : FragmentStateAdapter(fragmentActivity) {

    override fun createFragment(position: Int): Fragment {
        return when (position) {
            0 -> StepikPart1Fragment()
            else -> StepikPart2Fragment()
        }
    }

    override fun getItemCount(): Int {
        return 2
    }
}