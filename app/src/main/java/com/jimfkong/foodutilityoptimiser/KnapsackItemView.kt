package com.jimfkong.foodutilityoptimiser

import android.content.Context
import android.util.AttributeSet
import android.view.LayoutInflater
import android.view.View
import android.widget.EditText
import android.widget.LinearLayout

class KnapsackItemView @JvmOverloads constructor(
        context: Context,
        attrs: AttributeSet? = null,
        defStyleAttr: Int = 0
) : LinearLayout(context, attrs, defStyleAttr)
{
    private lateinit var layout: LinearLayout
    private lateinit var nameView: EditText
    private lateinit var valueView: EditText
    private lateinit var weightView: EditText
    var itemId: Int = -1

    constructor(context: Context, root: LinearLayout) : this(context) {
        val layoutInflater = LayoutInflater.from(context)
        val view = layoutInflater.inflate(R.layout.knapsack_item, root, false)
        layout = view.findViewById(R.id.knapsack_item)
        layout.id = View.generateViewId()
        itemId = layout.id
        root.addView(layout)

        initViews()
    }

    private fun initViews() {
        nameView = layout.findViewById(R.id.item_name)
        valueView = layout.findViewById(R.id.item_value)
        weightView = layout.findViewById(R.id.item_weight)
    }

    fun getName(): String {
        return cleanText(nameView.text.toString())
    }

    fun getValue(): Int {
        return valueView.text.toString().toInt()
    }

    fun getWeight(): Int {
        return weightView.text.toString().toInt()
    }

    fun isValidState(): Boolean {
        return (hasText(nameView) &&
                hasText(valueView) &&
                hasText(weightView)
        )
    }

    private fun hasText(view: EditText): Boolean {
        return !view.text.toString().isNullOrEmpty()
    }

    private fun cleanText(input: String): String {
        return input.replace(",", "")
    }
}
