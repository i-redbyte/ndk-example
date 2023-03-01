package com.github.iredbyte.ndk_example.stepik.ui

import android.content.Context
import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.viewpager2.widget.ViewPager2
import com.github.iredbyte.ndk_example.R
import com.google.android.material.tabs.TabLayout
import com.google.android.material.tabs.TabLayoutMediator

class StepikActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_stepik)
        setupViews()
    }

    private fun setupViews() {
        setupPager()
    }

    private fun setupPager() {
        val viewPager: ViewPager2 = findViewById(R.id.view_pager)
        val tabLayout: TabLayout = findViewById(R.id.tab_layout)
        val pagerAdapter = StepikPageAdapter(this)
        viewPager.adapter = pagerAdapter
        TabLayoutMediator(tabLayout, viewPager) { tab, position ->
            val tabNames = listOf(getString(R.string.stepik_page_title_part1), getString(R.string.stepik_page_title_part2))
            tab.text = tabNames[position]
        }.attach()
    }

    companion object {
        fun newInstance(context: Context): Intent = Intent(context, StepikActivity::class.java)
    }
}