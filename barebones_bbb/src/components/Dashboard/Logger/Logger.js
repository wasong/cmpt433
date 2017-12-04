import React from 'react'
import Radium from 'radium'

const styles = {
  root: {
    height: '60vh',
    overflowY: 'scroll',
  },
}

const Logger = ({ logs }) => (
  <div style={styles.root}>
    {
      logs.map(log => <div>{log}</div>)
    }
  </div>
)

export default Radium(Logger)
