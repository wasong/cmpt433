import React from 'react'
import Radium from 'radium'

import Status from '../Status'

const styles = {
  root: {
    display: 'flex',
    height: '100%',
    position: 'relative',
    alignItems: 'center',
    padding: '0 10px',
  },
  component: {
    flex: 10,
    display: 'flex',
  },
}

const Card = ({ children, statusType }) => (
  <div style={styles.root}>
    <div style={styles.component}>{children}</div>
    <Status type={statusType} />
  </div>
)

Card.defaultProps = {
  statusType: 'error',
}

export default Radium(Card)
