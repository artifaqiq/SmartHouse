class CreateSensors < ActiveRecord::Migration
  def change
    create_table :sensors do |t|

      t.integer :temperature
      t.integer :humidity
      t.integer :illumination

      t.timestamps null: false
    end
  end
end
