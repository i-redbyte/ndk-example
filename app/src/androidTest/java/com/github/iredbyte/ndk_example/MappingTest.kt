package com.github.iredbyte.ndk_example

import androidx.test.ext.junit.runners.AndroidJUnit4
import org.junit.Assert.*
import org.junit.Test
import org.junit.runner.RunWith

@RunWith(AndroidJUnit4::class)
class MappingTest {
    data class ObjectNative(val name: String? = "", val length: Int? = -1) : INative<ObjectNative, ObjectDomain> {
        override fun toDomain() = ObjectDomain(name ?: "", length ?: -1)
    }

    data class ObjectDomain(var name: String, val length: Int) : IDomain<ObjectDomain, ObjectNative> {
        override fun toNative() = ObjectNative(
            name.takeIf { name != "" },
            length.takeIf { it != -1 }
        )
    }

    @Test
    fun typeConversion() {
        val nativeObj = ObjectNative("C++", 1917)
        assert(nativeObj == nativeObj.toDomain().toNative())
        val emptyNativeObj = ObjectNative()
        assert(emptyNativeObj.toDomain().length == -1)
        assert(emptyNativeObj.toDomain().name == "")
    }
}