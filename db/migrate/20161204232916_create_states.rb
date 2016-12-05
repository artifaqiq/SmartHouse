class CreateStates < ActiveRecord::Migration
  def change
    create_table :states do |t|
      t.timestamps null: false

      t.boolean "relay1_requested", null: false, default: true
      t.boolean "relay1_actual", null: false, default: true
    end
  end
end
