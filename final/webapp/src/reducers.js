import { combineReducers } from 'redux'

import app from './app.module'
import dashboard from './components/Dashboard/dashboard.module'

export default combineReducers({
  app,
  dashboard,
})
