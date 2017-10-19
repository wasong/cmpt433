import { createStore, applyMiddleware, compose } from 'redux'
import thunk from 'redux-thunk'
import logger from 'redux-logger'

import rootReducer from './reducers'

export function configureStore(initialState = {}) {
  // Middleware and store enhancers
  const enhancers = [
    applyMiddleware(thunk, logger),
  ]

  const store = createStore(rootReducer, initialState, compose(...enhancers))

  // For hot reloading reducers
  if (module.hot) {
    module.hot.accept('./reducers', () => {
      const nextReducer = require('./reducers').default // eslint-disable-line

      store.replaceReducer(nextReducer)
    })
  }

  return store
}

export default configureStore
