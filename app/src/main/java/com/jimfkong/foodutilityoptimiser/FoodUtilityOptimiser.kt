package com.jimfkong.foodutilityoptimiser

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.view.*
import android.widget.EditText
import android.widget.LinearLayout

import kotlinx.android.synthetic.main.activity_food_utility_optimiser.*

class FoodUtilityOptimiser : AppCompatActivity() {
    private var items: ArrayList<KnapsackItemView> = ArrayList()
    private lateinit var listRoot: LinearLayout

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_food_utility_optimiser)
        setSupportActionBar(toolbar)

//        val response = Knapsack().PassKotlinObject(
//                KnapsackRequest(
//                        arrayOf("1,100,3", "2,20,2", "3,60,4", "4,40,1"),
//                        5
//                )
//        )

        listRoot = findViewById(R.id.item_list)

        addItem(listRoot)
    }


    fun createItem(view: View) {
        addItem(listRoot)
    }

    private fun addItem(listRoot: LinearLayout) {
        val item = KnapsackItemView(baseContext, listRoot)
        items.add(item)

    }

    fun deleteItem(view: View) {
        items.remove(items.find { x -> x.itemId == (view.parent as LinearLayout).id })
        listRoot.removeView(view.parent as LinearLayout)
    }

    fun calculate(view: View) {
        val request = KnapsackRequest(
            arrayOf(),
            getWeight()
        )

        for (item in items) {
            request.items += (
                    item.getName() + ',' +
                    item.getValue().toString() + ',' +
                    item.getWeight()
            )
        }

        val x = Knapsack().PassKotlinObject(request)
    }

    private fun getWeight(): Int {
        return (findViewById<EditText>(R.id.max_weight)).text.toString().toInt()
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.menu_food_utility_optimiser, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        return when(item.itemId) {
            R.id.action_settings -> true
            else -> super.onOptionsItemSelected(item)
        }
    }
}
