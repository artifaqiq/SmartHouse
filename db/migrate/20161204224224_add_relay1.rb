class AddRelay1 < ActiveRecord::Migration
  def change
    create_table :states do |t|
      t.boolean :on, null: false, default: false
    end
  end
end
