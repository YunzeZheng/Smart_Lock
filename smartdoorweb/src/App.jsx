// App.js
import React from 'react';
import { HashRouter as Router, Route, Routes, Link } from 'react-router-dom'; // Change to HashRouter
import { useState } from 'react';
import { Home, Info } from 'lucide-react';
import { Lock, Unlock } from 'lucide-react';
import './App.css';

// Navbar Component
const Navbar = () => {
  return (
    <nav className="bg-blue-600 p-4">
      <div className="container mx-auto flex justify-between items-center">
        <Link to="/" className="text-white text-xl font-bold flex items-center">
          <Lock className="mr-2" /> Smart Door
        </Link>
        <div className="flex space-x-4">
          <NavLink to="/" icon={<Home />}>Home</NavLink>
          <NavLink to="/lockcontrol" icon={<Lock />}>LockControl</NavLink>
          <NavLink to="/about" icon={<Info />}>About</NavLink>
        </div>
      </div>
    </nav>
  );
};

const NavLink = ({ to, children, icon }) => (
  <Link 
    to={to} 
    className="text-white hover:text-blue-200 flex items-center"
  >
    {icon}
    <span className="ml-1">{children}</span>
  </Link>
);

// Start Page Component
const StartPage = () => {
  return (
    <div className="min-h-screen bg-gray-100">
      <div className="container mx-auto px-4 py-8">
        <h1 className="text-4xl font-bold mb-6">Welcome to Smart Door Access</h1>
        <div className="grid md:grid-cols-2 gap-8">
          <div className="bg-white p-6 rounded-lg shadow-lg">
            <h2 className="text-2xl font-bold mb-4">Getting Started</h2>
            <ol className="list-decimal pl-6 space-y-4">
              <li>Create your account to begin managing your smart door</li>
              <li>Connect your smart door device using the provided QR code</li>
              <li>Set up your preferred authentication methods</li>
              <li>Start managing access and monitoring your door</li>
            </ol>
          </div>
          <div className="bg-white p-6 rounded-lg shadow-lg">
            <h2 className="text-2xl font-bold mb-4">Key Features</h2>
            <ul className="space-y-4">
              <li>✓ Remote access control</li>
              <li>✓ Digital key management</li>
              <li>✓ Instant notifications</li>
              <li>✓ Access history logging</li>
            </ul>
          </div>
        </div>
      </div>
    </div>
  );
};

// Home Page Component
const HomePage = () => {
  const [doorStatus, setDoorStatus] = useState('Locked');
  
  return (
    <div className="container mx-auto px-4 py-8">
      <div className="grid md:grid-cols-2 gap-8">
        <div className="bg-white p-6 rounded-lg shadow-lg">
          <h2 className="text-2xl font-bold mb-4">Door Status</h2>
          <div className="flex items-center justify-between mb-4">
            <span>Current Status:</span>
            <span className={`font-bold ${doorStatus === 'Locked' ? 'text-green-600' : 'text-red-600'}`}>
              {doorStatus}
            </span>
          </div>
          <button
            onClick={() => setDoorStatus(doorStatus === 'Locked' ? 'Unlocked' : 'Locked')}
            className="w-full bg-blue-600 text-white py-2 rounded hover:bg-blue-700"
          >
            Toggle Lock
          </button>
        </div>
        <div className="bg-white p-6 rounded-lg shadow-lg">
          <h2 className="text-2xl font-bold mb-4">Recent Activity</h2>
          <div className="space-y-2">
            {/* Placeholder for activity feed */}
            <div className="p-2 bg-gray-100 rounded">
              Door unlocked - 2:30 PM
            </div>
            <div className="p-2 bg-gray-100 rounded">
              Motion detected - 2:15 PM
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

// Video Stream Page Component
const LockControl = () => {
  const [doorStatus, setDoorStatus] = useState('Locked');

  // Function to toggle the lock status
  const toggleLock = () => {
    setDoorStatus((prevStatus) => (prevStatus === 'Locked' ? 'Unlocked' : 'Locked'));
  };

  return (
    <div className="container mx-auto px-4 py-8">
      <h2 className="text-3xl font-bold mb-6">Remote Door Control</h2>
      <div className="bg-white p-6 rounded-lg shadow-lg">
        <div className="flex items-center justify-between mb-8">
          <span className="text-xl">Door Status:</span>
          <span className={`text-2xl font-bold ${doorStatus === 'Locked' ? 'text-green-600' : 'text-red-600'}`}>
            {doorStatus}
          </span>
        </div>
        <div className="flex justify-center items-center">
          {doorStatus === 'Locked' ? (
            <Unlock className="text-blue-600 w-12 h-12 mr-4" />
          ) : (
            <Lock className="text-red-600 w-12 h-12 mr-4" />
          )}
          <button
            onClick={toggleLock}
            className={`bg-${doorStatus === 'Locked' ? 'red' : 'blue'}-600 text-white py-3 px-6 rounded-lg hover:bg-${
              doorStatus === 'Locked' ? 'red' : 'blue'
            }-700`}
          >
            {doorStatus === 'Locked' ? 'Unlock Door' : 'Lock Door'}
          </button>
        </div>
      </div>
    </div>
  );
};

// About Page Component
const AboutPage = () => {
  return (
    <div className="container mx-auto px-4 py-8">
      <div className="bg-white p-6 rounded-lg shadow-lg">
        <h2 className="text-2xl font-bold mb-4">About Smart Door Access</h2>
        <div className="space-y-4">
          <p>
            Smart Door Access Management System is a real-time embedded solution designed to address 
            traditional mechanical lock issues. Our system provides a flexible, digital alternative 
            that leverages cutting-edge technology for enhanced security and convenience.
          </p>
          <h3 className="text-xl font-semibold">Key Features:</h3>
          <ul className="list-disc pl-6">
            <li>Real-time processing for instant access control</li>
            <li>Digital key management with sharing capabilities</li>
            <li>RFID and biometric authentication options</li>
            <li>Real-time notifications and monitoring</li>
            <li>Secure and reliable embedded system</li>
          </ul>
          <p>
            Our system integrates various hardware and software components into a cohesive, 
            reliable, and secure solution suitable for modern, connected households.
          </p>
        </div>
      </div>
    </div>
  );
};

// Main App Component
const App = () => {
  return (
    // Set the basename to your subdirectory path
    <Router>
      <div className="min-h-screen bg-gray-100">
        <Navbar />
        <Routes>
          <Route path="/" element={<StartPage />} />
          <Route path="/home" element={<HomePage />} />
          <Route path="/lockcontrol" element={<LockControl />} />
          <Route path="/about" element={<AboutPage />} />
        </Routes>
      </div>
    </Router>
  );
};

export default App;
