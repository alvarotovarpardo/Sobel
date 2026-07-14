package com.example.sobelandroid

import android.graphics.Bitmap
import android.graphics.ImageDecoder
import android.os.Build
import android.os.Bundle
import android.provider.MediaStore
import android.util.Log
import androidx.activity.result.contract.ActivityResultContracts
import androidx.appcompat.app.AppCompatActivity
import com.example.sobelandroid.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private var currentBitmap: Bitmap? = null

    init {
        System.loadLibrary("sobelandroid") // Ajustado al nombre real de tu CMakeLists
    }

    private external fun applySobelNative(bitmap: Bitmap)

    private val pickImageLauncher = registerForActivityResult(ActivityResultContracts.GetContent()) { uri ->
        uri?.let {
            try {
                val sourceBitmap = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
                    val source = ImageDecoder.createSource(contentResolver, it)
                    ImageDecoder.decodeBitmap(source)
                } else {
                    @Suppress("DEPRECATION")
                    MediaStore.Images.Media.getBitmap(contentResolver, it)
                }
                
                currentBitmap = sourceBitmap.copy(Bitmap.Config.ARGB_8888, true)
                binding.imageView.setImageBitmap(currentBitmap)
                Log.i("SobelApp", "Image loaded successfully")
            } catch (e: Exception) {
                Log.e("SobelApp", "Error loading image", e)
            }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.btnLoadImage.setOnClickListener {
            pickImageLauncher.launch("image/*")
        }

        binding.btnApplyFilter.setOnClickListener {
            currentBitmap?.let { bmp ->
                applySobelNative(bmp)
                binding.imageView.invalidate()
                Log.i("SobelApp", "Filter applied and UI updated")
            } ?: Log.w("SobelApp", "No image loaded")
        }
    }
}