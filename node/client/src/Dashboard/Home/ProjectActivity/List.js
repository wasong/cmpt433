import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'
import RaisedButton from 'material-ui/RaisedButton'

import socket from '../../../utils/socket'

const styles = {
  root: {
    overflowY: 'auto',
    height: '100%',
  },
}

const handleSendData = () => {
  socket.emit('message', 'Sent from list!')
}

const List = props => (
  <div style={styles.root}>
    <RaisedButton label="Primary" onClick={handleSendData} primary />
  </div>
)

List.propTypes = {}
List.defaultProps = {}

export default Radium(List)
