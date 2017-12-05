import React from 'react'
import Radium from 'radium'

const styles = {
  root: {
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'center',
    width: 10,
    height: 10,
    borderRadius: '50%',
  },
  error: {
    backgroundColor: 'red',
  },
  success: {
    backgroundColor: 'green',
  },
}

const Status = ({ type, children }) => (
  <div style={[styles.root, styles[type]]} />
)

Status.defaultProps = {
  type: 'error',
}

export default Radium(Status)
