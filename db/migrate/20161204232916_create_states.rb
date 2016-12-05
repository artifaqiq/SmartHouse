class CreateStates < ActiveRecord::Migration
  def change
    create_table :states do |t|
      t.timestamps null: false

      t.boolean "relay1", null: false, default: true
    end
  end
end
