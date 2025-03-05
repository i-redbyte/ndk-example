package com.github.iredbyte.ndk_example.ndkman.keyvalue

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.widget.ArrayAdapter
import android.widget.EditText
import android.widget.Spinner
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.AppCompatButton
import com.github.iredbyte.ndk_example.R
import com.github.iredbyte.ndk_example.ndkman.storage.NdkMan
import java.util.Locale
import java.util.regex.Pattern

class NdkManActivity : AppCompatActivity() {
    private val keyPattern: Pattern = Pattern.compile("\\p{Alnum}+")
    private val etKey: EditText by lazy { findViewById(R.id.etKey) }
    private val etValue: EditText by lazy { findViewById(R.id.etValue) }
    private val btnGetValue: AppCompatButton by lazy { findViewById(R.id.btnGetValue) }
    private val btnSetValue: AppCompatButton by lazy { findViewById(R.id.btnSetValue) }
    private val spType: Spinner by lazy { findViewById(R.id.spType) }
    private val store = NdkMan()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_ndk_man)
        val adapter: ArrayAdapter<StoreType> =
            ArrayAdapter(this, android.R.layout.simple_spinner_item, StoreType.values())
        spType.adapter = adapter
        btnGetValue.setOnClickListener { onGetValue() }
        btnSetValue.setOnClickListener { onSetValue() }
    }

    private fun onSetValue() {
        val key = etKey.text.toString()
        val value = etValue.text.toString()
        val type: StoreType = spType.selectedItem as StoreType
        if (!keyPattern.matcher(key).matches()) {
            displayMessage("Incorrect key")
            return
        }
        try {
            when (type) {
                StoreType.String -> store.setString(key, value)
                StoreType.Integer -> store.setInteger(key, value.toInt())
                StoreType.Boolean -> store.setBoolean(key, true)
                StoreType.Float -> store.setFloat(key, value.toFloat())
                StoreType.Double -> store.setDouble(key, value.toDouble())
            }
        } catch (ex: Exception) {
            displayMessage("Incorrect value.")
        }
        printCountEntries()
    }

    private fun printCountEntries() {
        val numEntries = store.count
        Log.d("", "Store $numEntries")
    }

    private fun onGetValue() {
        val key = etKey.text.toString()
        val type: StoreType = spType.selectedItem as StoreType
        if (!keyPattern.matcher(key).matches()) {
            displayMessage("Incorrect key")
            return
        }
        when (type) {
            StoreType.Double -> {
                etValue.setText(
                    String.format(
                        Locale.getDefault(),
                        "%.4f",
                        store.getDouble(key)
                    )
                )
            }

            StoreType.Float -> {
                etValue.setText(
                    String.format(
                        Locale.getDefault(),
                        "%.2f",
                        store.getFloat(key)
                    )
                )
            }

            StoreType.Integer -> {
                etValue.setText(
                    String.format(
                        Locale.getDefault(),
                        "%d",
                        store.getInteger(key)
                    )
                )
            }

            StoreType.String -> {
                etValue.setText(store.getString(key))
            }

            StoreType.Boolean -> {
                etValue.setText(store.getBoolean(key).toString())
            }
        }
    }

    private fun displayMessage(text: String) {
        Toast.makeText(this, text, Toast.LENGTH_LONG).show()
    }

    companion object {
        fun newInstance(context: Context): Intent =
            Intent(context, NdkManActivity::class.java)
    }
}