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
    end
  end

end
