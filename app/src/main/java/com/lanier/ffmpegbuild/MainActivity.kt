package com.lanier.ffmpegbuild

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.lanier.ffmpegbuild.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = ffmpegVersion()
    }

    /**
     * A native method that is implemented by the 'ffmpegbuild' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun ffmpegVersion(): String

    external fun executeCommand(command: String): Int

    external fun executeCommandWithProgress(command: String)

    companion object {
        // Used to load the 'ffmpegbuild' library on application startup.
        init {
            System.loadLibrary("ffmpegbuild")
//            System.loadLibrary("avcodec")
//            System.loadLibrary("avdevice")
//            System.loadLibrary("avfilter")
//            System.loadLibrary("avformat")
//            System.loadLibrary("avutil")
//            System.loadLibrary("postproc")
//            System.loadLibrary("swresample")
//            System.loadLibrary("swscale")
        }
    }
}