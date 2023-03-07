package com.github.iredbyte.ndk_example

interface INative<SELF : INative<SELF, TDOMAIN>, TDOMAIN : IDomain<TDOMAIN, SELF>> {
    fun toDomain(): TDOMAIN
}

interface IDomain<SELF : IDomain<SELF, TNATIVE>, TNATIVE : INative<TNATIVE, SELF>> {
    fun toNative(): TNATIVE
}

// Example:

//data class ObjectData(val name: String?, val length: Int?) : INative<ObjectData, ObjectDomain> {
//    override fun toDomain() = ObjectDomain(name ?: "", length ?: -1)
//}
//
//data class ObjectDomain(var name: String, val length: Int) : IDomain<ObjectDomain, ObjectData> {
//    override fun toNative() = ObjectData(name, length)
//}
//
//fun main() {
//    val a = ObjectData("Null", 100)
//    assert(a == a.toDomain().toNative())
//
//}

