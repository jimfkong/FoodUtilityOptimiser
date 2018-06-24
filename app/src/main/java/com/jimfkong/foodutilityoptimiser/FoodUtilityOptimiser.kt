package com.jimfkong.foodutilityoptimiser

import android.os.Bundle
import android.support.v7.app.AlertDialog
import android.support.v7.app.AppCompatActivity
import android.view.*
import android.widget.EditText
import android.widget.LinearLayout
import android.widget.Toast

import kotlinx.android.synthetic.main.activity_food_utility_optimiser.*

// TODO Need to handle commas and stuff
// TODO figure out why weight of 1 doesn't seem to work?

class FoodUtilityOptimiser : AppCompatActivity() {
    private var items: ArrayList<KnapsackItemView> = ArrayList()
    private lateinit var listRoot: LinearLayout
    private lateinit var weightView: EditText

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

        weightView = findViewById(R.id.max_weight)
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
        if (!canCalculate()) {
            Toast.makeText(this, "Please fill in all the fields", Toast.LENGTH_SHORT).show()
            return
        }

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

        val result = Knapsack().PassKotlinObject(request)

        showDialog(formatResult(result))
    }

    private fun formatResult(result: String): String {
        if (result.isNullOrEmpty()) {
            return result
        }

        return result.replace(',', '\n')
    }

    private fun canCalculate(): Boolean {
        if (weightView.text.toString().isNullOrEmpty()) {
            return false
        }

        for (item in items) {
            if (!item.isValidState()) {
                return false
            }
        }

        return true
    }

    private fun showDialog(text: String) {
        val dialogBuilder = AlertDialog.Builder(this)

        with(dialogBuilder) {
            setTitle("What to eat")
            setMessage(if (text.isEmpty()) "Nothing!" else text)
            setPositiveButton("Dismiss") {
                dialog, _ ->
                dialog.dismiss()
            }
        }

        val dialog = dialogBuilder.create()
        dialog.show()
    }

    private fun getWeight(): Int {
        return weightView.text.toString().toInt()
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
