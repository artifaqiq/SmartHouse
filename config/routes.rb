Rails.application.routes.draw do

  devise_for :users
  root 'welcome#index'

  scope '/api' do
    scope '/sensors' do
      get '/online' => 'sensors#show'
      post '/update' => 'sensors#create'
    end

    scope '/states' do
      get '/show' => 'states#show'
      post '/update' => 'states#update'
      get '/relay1_requested' => 'states#show_relay1_requested'
    end
  end

end
